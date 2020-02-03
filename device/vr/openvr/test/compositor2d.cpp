#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/matrix.h"

namespace compositor2d {

// constants
constexpr float nearValue = 0.1f;
constexpr float farValue = 1000.0f;
const char *hlsl = R"END(
cbuffer VS_CONSTANT_BUFFER : register(b0)
{
  float4x4 viewMatrix;
  float4x4 projectionMatrix;
  float2 _ZBufferParams;
  float2 tmp1;
  float4x3 tmp2;
}

/* cbuffer PS_CONSTANT_BUFFER : register(b0)
{
  float width;
  float height;
  float tmpps11;
  float tmpps12;
  float tmpps13;
  float tmpps14;
  float tmpps15;
  float tmpps16;
} */

//------------------------------------------------------------//
// Structs
//------------------------------------------------------------//
// Vertex shader OUT struct
struct VS_OUTPUT
{
   float4 Position: SV_POSITION;
   float2 Uv: TEXCOORD0;
   float4 ScreenCoords: TEXCOORD1;
   float4 Position2: POSITION0;
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
Texture2D DepthTexture : register(ps, t1);
SamplerState QuadTextureSampler {
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};
//------------------------------------------------------------//

VS_OUTPUT vs_main(float2 inPos : POSITION, float2 inTex : TEXCOORD0)
{
  VS_OUTPUT Output;
  float2 xy = inPos.xy * 0.5;
  xy.y += 1;
  float4 p = mul(viewMatrix, float4(xy, -1, 1));
  Output.Position = mul(projectionMatrix, p);
  Output.ScreenCoords = Output.Position;
  Output.Position2 = Output.Position;
  // Output.Depth = Output.Position.z/Output.Position.w;
  // Output.Position = mul(viewMatrix, float4(inPos * 0.5, 0, 1));
  // Output.Position = viewMatrix * float4(inPos * 0.5, 0, 1);
  Output.Uv = float2(inTex.x, 1 - inTex.y);
  return Output;
}

inline float LinearEyeDepth( float z ) {
  return 1.0 / (_ZBufferParams.x * z + _ZBufferParams.y);
}

PS_OUTPUT ps_main(VS_OUTPUT IN)
{
  PS_OUTPUT result;
  
  float depthScale = 1000;

  float d = IN.Position2.z + 0.1;
  // d = LinearEyeDepth(d);
  float2 screenPos = IN.ScreenCoords.xy/IN.ScreenCoords.w * 0.5 + 0.5;
  screenPos.y = 1-screenPos.y;
  float e = DepthTexture.Sample(QuadTextureSampler, screenPos).r;

  /* result.Color = float4(IN.Uv.x, 0, IN.Uv.y, 1);
  result.Depth = 1; */

  // e *= depthScale;
  /* if (d < 0.5) {
    result.Color = float4(d, 0, 0, 1);
    result.Depth = d;
  } else if (d < 1) {
    result.Color = float4(0, d, 0, 1);
    result.Depth = d;
  } else {
    result.Color = float4(0, 0, d, 1);
    result.Depth = d;
  } */

  if (e == 1.0 || d < (e*depthScale)) {
    result.Color = float4(QuadTexture.Sample(QuadTextureSampler, IN.Uv).rgb, 1);
    result.Depth = d/depthScale;
  } else {
    discard;
  }

  return result;
}

//------------------------------------------------------------//
)END";

// globals
HANDLE backbufferShHandleLatched = NULL;
ID3D11Texture2D *backbufferShTex = nullptr;
ID3D11ShaderResourceView *backbufferShResourceView = nullptr;

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

void init2DShader(ID3D11Device5 *device, ID3D11DeviceContext4 *context, IDXGISwapChain *swapChain) {
  getOut() << "init shader 2d 1" << std::endl;
  
  HRESULT hr;
  {
    D3D11_BUFFER_DESC cbDesc{};
    cbDesc.ByteWidth = 16 * 3 * sizeof(float);
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
  // getOut() << "init render 4" << std::endl;
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
void blendWindow(
  ID3D11Device5 *device,
  ID3D11DeviceContext4 *context,
  IDXGISwapChain *swapChain,
  int iEye,
  ID3D11ShaderResourceView *backbufferIn,
  ID3D11RenderTargetView *colorRenderTarget,
  ID3D11RenderTargetView *depthRenderTarget,
  ID3D11ShaderResourceView *depthIn
) {
  ID3D11ShaderResourceView *localShaderResourceViews[2] = {
    backbufferIn,
    depthIn
  };

  float localUniforms[16*3] = {};

  float eyeToHeadMatrix[16];
  vr::HmdMatrix34_t matEyeRight = vr::g_vrsystem->GetEyeToHeadTransform(iEye == 0 ? vr::Eye_Left : vr::Eye_Right);
  setPoseMatrix(eyeToHeadMatrix, matEyeRight);

  float headToEyeMatrix[16];
  getMatrixInverse(eyeToHeadMatrix, headToEyeMatrix);

  float hmdMatrix[16];
  vr::TrackedDevicePose_t renderPoses[vr::k_unMaxTrackedDeviceCount];
  vr::g_pvrcompositor->GetCachedLastPoses(renderPoses, ARRAYSIZE(renderPoses), nullptr, 0);
  for (unsigned int i = 0; i < ARRAYSIZE(renderPoses); i++) {
    const vr::TrackedDevicePose_t &trackedDevicePose = renderPoses[i];

    if (trackedDevicePose.bPoseIsValid) {
      const vr::ETrackedDeviceClass deviceClass = vr::g_vrsystem->GetTrackedDeviceClass(i);

      if (deviceClass == vr::TrackedDeviceClass_HMD) {
        setPoseMatrix(hmdMatrix, trackedDevicePose.mDeviceToAbsoluteTracking);
        break;
      }
    }
  }
  float hmdMatrixInverse[16];
  getMatrixInverse(hmdMatrix, hmdMatrixInverse);

  multiplyMatrices(headToEyeMatrix, hmdMatrixInverse, localUniforms);
  
  vr::HmdMatrix44_t projectionMatrix = vr::g_vrsystem->GetProjectionMatrix(iEye == 0 ? vr::Eye_Left : vr::Eye_Right, nearValue, farValue);
  for (unsigned int v = 0; v < 4; v++) {
    for (unsigned int u = 0; u < 4; u++) {
      localUniforms[16 + v * 4 + u] = projectionMatrix.m[u][v];
    }
  }

  {
    const float c1 = farValue / nearValue;
    const float c0 = 1.0f - c1;
    
    localUniforms[16*2] = c0/farValue;
    localUniforms[16*2 + 1] = c1/farValue;
  }
  
  /* getOut() << "render 2d window:\n";
  for (size_t i = 0; i < 16; i++) {
    getOut() << eyeToHeadMatrix[i] << " ";
  }
  getOut() << "\n";
  for (size_t i = 0; i < 16; i++) {
    getOut() << headToEyeMatrix[i] << " ";
  }
  getOut() << "\n";
  for (size_t i = 0; i < 16; i++) {
    getOut() << hmdMatrix[i] << " ";
  }
  getOut() << "\n";
  for (size_t i = 0; i < 16*2; i++) {
    if (i % 16 == 0) {
      getOut() << "\n";
    }
    getOut() << localUniforms[i] << " ";
  }
  getOut() << std::endl; */

  context->UpdateSubresource(uniformsConstantBuffer, 0, 0, localUniforms, 0, 0);

  context->VSSetShader(vsShader, nullptr, 0);
  context->PSSetShader(psShader, nullptr, 0);
  context->PSSetShaderResources(0, ARRAYSIZE(localShaderResourceViews), localShaderResourceViews);
  context->VSSetConstantBuffers(0, 1, &uniformsConstantBuffer);
  // context->PSSetConstantBuffers(0, 0, nullptr);
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
  context->OMSetRenderTargets(ARRAYSIZE(localRenderTargetViews), localRenderTargetViews, nullptr);

  D3D11_VIEWPORT viewport{
    0, // TopLeftX,
    0, // TopLeftY,
    vr::g_pvrcompositor->width, // Width,
    vr::g_pvrcompositor->height, // Height,
    0, // MinDepth,
    1 // MaxDepth
  };
  context->RSSetViewports(1, &viewport);
  context->DrawIndexed(6, 0, 0);
  
  ID3D11ShaderResourceView *localShaderResourceViewsClear[ARRAYSIZE(localShaderResourceViews)] = {};
  context->PSSetShaderResources(0, ARRAYSIZE(localShaderResourceViewsClear), localShaderResourceViewsClear);
  ID3D11RenderTargetView *localRenderTargetViewsClear[ARRAYSIZE(localRenderTargetViews)] = {};
  context->OMSetRenderTargets(ARRAYSIZE(localRenderTargetViewsClear), localRenderTargetViewsClear, nullptr);
}
void homeRenderLoop() {
  ID3D11Device5 *device = vr::g_pvrcompositor->device.Get();
  ID3D11DeviceContext4 *context = vr::g_pvrcompositor->context.Get();
  IDXGISwapChain *swapChain = vr::g_pvrcompositor->swapChain.Get();
  
  init2DShader(device, context, swapChain);
  
  for (;;) {
    vr::TrackedDevicePose_t renderPoses[vr::k_unMaxTrackedDeviceCount];
    vr::TrackedDevicePose_t gamePoses[vr::k_unMaxTrackedDeviceCount];
    vr::g_pvrcompositor->WaitGetPoses(renderPoses, ARRAYSIZE(renderPoses), gamePoses, ARRAYSIZE(gamePoses));

    if (vr::g_pvrcompositor->backbufferSrv) {
      for (int iEye = 0; iEye < 2; iEye++) {
        vr::g_pvrcompositor->fnp.lock_guard([&]() -> void {
          blendWindow(
            device,
            context,
            swapChain,
            iEye,
            vr::g_pvrcompositor->backbufferSrv,
            vr::g_pvrcompositor->renderTargetViews[iEye],
            vr::g_pvrcompositor->renderTargetDepthBackViews[iEye],
            vr::g_pvrcompositor->depthShaderFrontResourceViews[iEye]
          );
          vr::g_pvrcompositor->SwapDepthTex(iEye);
        });
        vr::g_pvrcompositor->Submit(iEye == 0 ? vr::Eye_Left : vr::Eye_Right, nullptr, nullptr, vr::EVRSubmitFlags::Submit_Default);
      }
    } else {
      vr::g_pvrcompositor->Submit(vr::Eye_Left, nullptr, nullptr, vr::EVRSubmitFlags::Submit_Default);
      vr::g_pvrcompositor->Submit(vr::Eye_Right, nullptr, nullptr, vr::EVRSubmitFlags::Submit_Default);
    }
  }
}

}