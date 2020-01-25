#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/compositorproxy.h"

/* extern HRESULT (STDMETHODCALLTYPE *RealCreateTexture2D)(
  ID3D11Device *This,
  const D3D11_TEXTURE2D_DESC   *pDesc,
  const D3D11_SUBRESOURCE_DATA *pInitialData,
  ID3D11Texture2D              **ppTexture2D
); */

namespace compositor2d {

// constants
const char *hlsl = R"END(
cbuffer VS_CONSTANT_BUFFER : register(b0)
{
  float flip;
  float eyeTexOffset;
  float tmpvs11;
  float tmpvs12;
  float tmpvs13;
  float tmpvs14;
  float tmpvs15;
  float tmpvs16;
}

cbuffer PS_CONSTANT_BUFFER : register(b0)
{
  float width;
  float height;
  float tmpps11;
  float tmpps12;
  float tmpps13;
  float tmpps14;
  float tmpps15;
  float tmpps16;
}

cbuffer PS_CONSTANT_BUFFER : register(b1)
{
  float2 _ZBufferParams;
  float4 depthColor;
  float tmpps21;
  float tmpps22;
}

//------------------------------------------------------------//
// Structs
//------------------------------------------------------------//
// Vertex shader OUT struct
struct VS_OUTPUT
{
   float4 Position: SV_POSITION;
   float2 Uv: TEXCOORD0;
   float2 Tex1: TEXCOORD1;
};
//------------------------------------------------------------//
// Pixel Shader OUT struct
struct PS_OUTPUT
{
  float4 Color : SV_Target0;
  float Depth : SV_Target1;
};
//------------------------------------------------------------//

//------------------------------------------------------------//
// Textures / samplers
//------------------------------------------------------------//
//Texture
Texture2D QuadTexture : register(ps, t0);
Texture2D QuadDepthTexture : register(ps, t1);
Texture2DMS<float4> QuadDepthTextureMS : register(ps, t2);
Texture2D DepthTexture : register(ps, t3);
SamplerState QuadTextureSampler {
  MipFilter = NONE;
  MinFilter = POINT;
  MagFilter = POINT;
};
//------------------------------------------------------------//

VS_OUTPUT vs_main(float2 inPos : POSITION, float2 inTex : TEXCOORD0)
{
  VS_OUTPUT Output;
  Output.Position = float4(inPos, 0, 1);
  Output.Uv = float2(inTex.x, (flip > 0) ? inTex.y : (1-inTex.y));
  Output.Tex1 = float2(inTex.x + eyeTexOffset, inTex.y);
  return Output;
}

/* // Unity
static const float4x4 projectionMatrix = {0.917286, -0, 0, 0, 0, -0.833537, 0, 0, -0.174072, 0.106141, 9.53674e-07, -1, 0, -0, 0.02, 0};
static const float m32 = projectionMatrix[3][2];
static const float m22 = projectionMatrix[2][2];
static const float near = m32 / (m22 + 1);
static const float far = m32 / (m22);
static const float4 _ZBufferParams = float4(-1+far/near, 1, (-1+far/near)/far, 1/far);

// Chrome
static const float4x4 projectionMatrixRaw = {0.917286, 0, -0.174072, 0, 0, 0.833537, -0.106141, 0, 0, 0, -1.0002, -0.20002, 0, 0, -1, 0};
static const float4x4 projectionMatrix = transpose(projectionMatrixRaw); // {0.917286, 0, 0, 0, 0, 0.833537, 0, 0, -0.174072, -0.106141, -1.0002, -1, 0, 0, -0.20002, 0};
static const float m32 = projectionMatrix[3][2];
static const float m22 = projectionMatrix[2][2];
static const float near = m32 / (m22 - 1);
static const float far = m32 / (m22 + 1);
static const float4 _ZBufferParams = float4(1-far/near, far/near, (1-far/near)/far, (far/near)/far); */

inline float LinearEyeDepth( float z ) {
  return 1.0 / (_ZBufferParams.x * z + _ZBufferParams.y);
}

PS_OUTPUT do_ps(float d, VS_OUTPUT IN)
{
  PS_OUTPUT result;

  float depthScale = 1000;

  d = LinearEyeDepth(d);
  float e = DepthTexture.Sample(QuadTextureSampler, IN.Uv).r;

  /* result.Color = float4(d * depthColor.rgb, 1);
  result.Depth = d; */

  /* if (d < 0.5) {
    result.Color = float4(d, 0, 0, 1);
    result.Depth = d;
  } else if (d < 1) {
    result.Color = float4(0, d, 0, 1);
    result.Depth = d;
  } else {
    result.Color = float4(0, 0, d, 1);
    result.Depth = e;
  } */

  if (e == 1.0 || d < (e*depthScale)) {
    result.Color = float4(QuadTexture.Sample(QuadTextureSampler, IN.Uv).rgb, 1);
    result.Depth = d/depthScale;
  } else {
    // result.Color = float4(0, 0, e, 1);
    // result.Depth = e;
    discard;
  }

  return result;
}

PS_OUTPUT ps_main(VS_OUTPUT IN)
{
  float d = QuadDepthTexture.Sample(QuadTextureSampler, IN.Tex1);
  return do_ps(d, IN);
}

PS_OUTPUT ps_main_ms(VS_OUTPUT IN)
{
  float d = QuadDepthTextureMS[uint2(IN.Tex1.x * width, IN.Tex1.y * height)].r;
  return do_ps(d, IN);
}

//------------------------------------------------------------//
)END";

// globals
// window
HWND twoDWindow = NULL;
ID3D11Texture2D *windowTex = nullptr;
RECT windowRect{};
uint32_t windowWidth = 0;
uint32_t windowHeight = 0;
IDXGISurface1 *windowGdiSurface = nullptr;
ID3D11ShaderResourceView *windowResourceView = nullptr;

// shader
ID3DBlob *vsBlob = nullptr;
ID3D11VertexShader *vsShader = nullptr;
ID3DBlob *psBlob = nullptr;
ID3D11PixelShader *psShader = nullptr;
ID3D11Buffer *uniformsConstantBuffer = nullptr;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
  char buffer[256];
  int written = GetWindowTextA(hwnd, buffer, sizeof(buffer));
  if (written && strstr(buffer, "Discord") != NULL) {
    *(HWND*)lParam = hwnd;
    return FALSE;
  }
  return TRUE;
}

HWND GetDiscordHwnd() {
  HWND hWnd = NULL;
  EnumWindows(EnumWindowsProc, (LPARAM)&hWnd);
  return hWnd;
}

void initShader(vr::PVRCompositor *pvrcompositor, ID3D11Device5 *device, ID3D11DeviceContext4 *context) {
  HRESULT hr;

  {
    D3D11_BUFFER_DESC cbDesc{};
    cbDesc.ByteWidth = 16 * 2 * sizeof(float);
    // cbDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    // cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    // cbDesc.MiscFlags = 0;
    // cbDesc.StructureByteStride = 0;

    // Create the buffer.
    hr = device->CreateBuffer(
      &cbDesc,
      NULL, 
      &uniformsConstantBuffer
    );
    if (FAILED(hr)) {
      getOut() << "uniforms cbuf create failed: " << (void *)hr << std::endl;
      abort();
    }
  }
  getOut() << "init render 4" << std::endl;
  {
    ID3DBlob *errorBlob = nullptr;
    hr = D3DCompile(
      hlsl,
      strlen(hlsl),
      "vs.hlsl",
      nullptr,
      D3D_COMPILE_STANDARD_FILE_INCLUDE,
      "vs_main",
      "vs_5_0",
      D3DCOMPILE_ENABLE_STRICTNESS,
      0,
      &vsBlob,
      &errorBlob
    );
    if (FAILED(hr)) {
      if (errorBlob != nullptr) {
        getOut() << "vs compilation failed: " << (char*)errorBlob->GetBufferPointer() << std::endl;
        abort();
      }
    }
    ID3D11ClassLinkage *linkage = nullptr;
    hr = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), linkage, &vsShader);
    if (FAILED(hr)) {
      getOut() << "vs create failed: " << (void *)hr << std::endl;
      abort();
    }
  }
  getOut() << "init render 5" << std::endl;
  {
    ID3DBlob *errorBlob = nullptr;
    hr = D3DCompile(
      hlsl,
      strlen(hlsl),
      "ps.hlsl",
      nullptr,
      D3D_COMPILE_STANDARD_FILE_INCLUDE,
      "ps_main",
      "ps_5_0",
      D3DCOMPILE_ENABLE_STRICTNESS,
      0,
      &psBlob,
      &errorBlob
    );
    getOut() << "init render 6 1" << std::endl;
    if (FAILED(hr)) {
      if (errorBlob != nullptr) {
        getOut() << "ps compilation failed: " << (char*)errorBlob->GetBufferPointer() << std::endl;
        abort();
      }
    }
    
    getOut() << "init render 7 1" << std::endl;

    ID3D11ClassLinkage *linkage = nullptr;
    hr = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), linkage, &psShader);
    if (FAILED(hr)) {
      getOut() << "ps create failed: " << (void *)hr << std::endl;
      abort();
    }
  }
}
void blendWindow(vr::PVRCompositor *pvrcompositor, ID3D11Device5 *device, ID3D11DeviceContext4 *context, int iEye, ID3D11RenderTargetView *colorRenderTarget, ID3D11RenderTargetView *depthRenderTarget, ID3D11ShaderResourceView *depthIn) {
  HRESULT hr;
  
  if (!twoDWindow) {
    twoDWindow = GetDiscordHwnd();
    if (!twoDWindow) {
      getOut() << "failed to get 2d window: " << (void *)GetLastError() << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }
    if (!GetWindowRect(twoDWindow, &windowRect)) {
      getOut() << "failed to get 2d window rect: " << (void *)GetLastError() << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }
    
    windowWidth = windowRect.right - windowRect.left;
    windowHeight = windowRect.bottom - windowRect.top;
    
    getOut() << "got window rect: " << windowRect.left << " " << windowRect.right << " " << windowRect.top << " " << windowRect.bottom << " " << windowWidth << " " << windowHeight << std::endl;

    // getOut() << "succ 0.1 " << (void *)RealCreateTexture2D << std::endl;

    D3D11_TEXTURE2D_DESC desc{};
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.Width = windowWidth;
    desc.Height = windowHeight;
    // desc.Width = desc.Height = 512;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    // desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // desc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    // desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
    // desc.BindFlags = 40; // D3D11_BIND_DEPTH_STENCIL
    desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // D3D11_BIND_DEPTH_STENCIL
    // desc.MiscFlags = 0; //D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
    desc.MiscFlags |= D3D11_RESOURCE_MISC_GDI_COMPATIBLE;

    hr = device->CreateTexture2D(
      &desc,
      NULL,
      &windowTex
    );
    if (FAILED(hr)) {
      getOut() << "failed to create 2d window tex: " << (void *)hr << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }
    
    // getOut() << "created 2d window tex" << std::endl;
    
    hr = windowTex->QueryInterface(__uuidof(IDXGISurface1), (void **)&windowGdiSurface);
    if (FAILED(hr)) {
      getOut() << "failed to get 2d window gdi surface: " << (void *)hr << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srv{};
    srv.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srv.Texture2D.MostDetailedMip = 0;
    srv.Texture2D.MipLevels = 1;

    hr = device->CreateShaderResourceView(
      windowTex,
      &srv,
      &windowResourceView
    );
    if (FAILED(hr)) {
      getOut() << "failed to get 2d window shader resource view: " << (void *)hr << std::endl;
      pvrcompositor->InfoQueueLog();
      abort();
    }
    
    getOut() << "created 2d window gdi surface" << std::endl;
  }
  
  // getOut() << "get gdi surface dc " << (void *)windowTex << " " << (void *)windowGdiSurface << std::endl;

  HDC dstDc = nullptr;
  hr = windowGdiSurface->GetDC(
    true, // discard contents
    &dstDc
  );
  if (FAILED(hr)) {
    getOut() << "failed to get 2d window dst hdc: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
  
  // getOut() << "get 2d window dc" << std::endl;
  
  HDC srcDc = GetWindowDC(twoDWindow);
  if (!srcDc) {
    getOut() << "failed to get 2d window src hdc: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
  
  // getOut() << "blitting 2d window tex" << std::endl;
  
  if (!BitBlt(
    dstDc,
    0,
    0,
    windowWidth,
    windowHeight,
    srcDc,
    0,
    0,
    SRCCOPY
  )) {
    getOut() << "failed to blit 2d window: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
  
  // getOut() << "blitted 2d window tex" << std::endl;
  
  hr = windowGdiSurface->ReleaseDC(nullptr);
  if (FAILED(hr)) {
    getOut() << "failed to release 2d window dst hdc: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }
  if (!ReleaseDC(twoDWindow, srcDc)) {
    getOut() << "failed to release 2d window src hdc: " << (void *)hr << " " << (void *)GetLastError() << std::endl;
    pvrcompositor->InfoQueueLog();
    abort();
  }

  ID3D11ShaderResourceView *localShaderResourceViews[2] = {
    windowResourceView,
    depthIn
  };
  float localUniforms[16*2];
  // XXX copy in
  context->UpdateSubresource(uniformsConstantBuffer, 0, 0, localUniforms, 0, 0);

  context->VSSetShader(vsShader, nullptr, 0);
  context->PSSetShader(psShader, nullptr, 0);
  context->PSSetShaderResources(0, ARRAYSIZE(localShaderResourceViews), localShaderResourceViews);
  context->VSSetConstantBuffers(0, 1, &uniformsConstantBuffer);
  // context->PSSetConstantBuffers(0, psConstantBuffers.size(), psConstantBuffers.data());
  /* D3D11_VIEWPORT viewport{
    0, // TopLeftX,
    0, // TopLeftY,
    width, // Width,
    height, // Height,
    0, // MinDepth,
    1 // MaxDepth
  };
  context->RSSetViewports(1, &viewport); */
  ID3D11RenderTargetView *localRenderTargetViews[2] = {
    colorRenderTarget,
    depthRenderTarget
  };
  context->OMSetRenderTargets(
    ARRAYSIZE(localRenderTargetViews),
    localRenderTargetViews,
    nullptr
  );
  context->DrawIndexed(6, 0, 0);
}

}