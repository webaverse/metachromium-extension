#include "device/vr/openvr/test/compositor2d.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"
#include "device/vr/openvr/test/compositorproxy.h"

extern HANDLE backbufferShHandle;

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

  /* // result.Color = float4(QuadTexture.Sample(QuadTextureSampler, IN.Uv).rgb, 1);
  result.Color = float4(IN.Uv.x, 0, IN.Uv.y, 1);
  result.Depth = e; */

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
    // result.Color = float4(0, 0, e, 1);
    // result.Depth = e;
    discard;
  }

  return result;
}

//------------------------------------------------------------//
)END";

// globals
ID3D11Device5 *device = nullptr;
ID3D11DeviceContext4 *context = nullptr;
IDXGISwapChain *swapChain = nullptr;

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
void setPoseMatrix(float *dstMatrixArray, const vr::HmdMatrix34_t &srcMatrix) {
  for (unsigned int v = 0; v < 4; v++) {
    for (unsigned int u = 0; u < 3; u++) {
      dstMatrixArray[v * 4 + u] = srcMatrix.m[u][v];
    }
  }
  dstMatrixArray[0 * 4 + 3] = 0;
  dstMatrixArray[1 * 4 + 3] = 0;
  dstMatrixArray[2 * 4 + 3] = 0;
  dstMatrixArray[3 * 4 + 3] = 1;
}
void getMatrixInverse(const float *inMatrix, float *outMatrix) {
  // based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
  float *te = outMatrix;
  const float *me = inMatrix;

  const float n11 = me[ 0 ], n21 = me[ 1 ], n31 = me[ 2 ], n41 = me[ 3 ],
    n12 = me[ 4 ], n22 = me[ 5 ], n32 = me[ 6 ], n42 = me[ 7 ],
    n13 = me[ 8 ], n23 = me[ 9 ], n33 = me[ 10 ], n43 = me[ 11 ],
    n14 = me[ 12 ], n24 = me[ 13 ], n34 = me[ 14 ], n44 = me[ 15 ],

    t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44,
    t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44,
    t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44,
    t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

  const float det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

  if (det == 0.0f) {
    getOut() << "Can't invert matrix, determinant is 0" << std::endl;
  }

  const float detInv = 1.0f / det;

  te[ 0 ] = t11 * detInv;
  te[ 1 ] = ( n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44 ) * detInv;
  te[ 2 ] = ( n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44 ) * detInv;
  te[ 3 ] = ( n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43 ) * detInv;

  te[ 4 ] = t12 * detInv;
  te[ 5 ] = ( n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44 ) * detInv;
  te[ 6 ] = ( n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44 ) * detInv;
  te[ 7 ] = ( n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43 ) * detInv;

  te[ 8 ] = t13 * detInv;
  te[ 9 ] = ( n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44 ) * detInv;
  te[ 10 ] = ( n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44 ) * detInv;
  te[ 11 ] = ( n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43 ) * detInv;

  te[ 12 ] = t14 * detInv;
  te[ 13 ] = ( n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34 ) * detInv;
  te[ 14 ] = ( n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34 ) * detInv;
  te[ 15 ] = ( n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33 ) * detInv;
}
void multiplyMatrices(const float *aMatrix, const float *bMatrix, float *outMatrix) {
  const float *ae = aMatrix;
  const float *be = bMatrix;
  float *te = outMatrix;

  const float a11 = ae[ 0 ], a12 = ae[ 4 ], a13 = ae[ 8 ], a14 = ae[ 12 ];
  const float a21 = ae[ 1 ], a22 = ae[ 5 ], a23 = ae[ 9 ], a24 = ae[ 13 ];
  const float a31 = ae[ 2 ], a32 = ae[ 6 ], a33 = ae[ 10 ], a34 = ae[ 14 ];
  const float a41 = ae[ 3 ], a42 = ae[ 7 ], a43 = ae[ 11 ], a44 = ae[ 15 ];

  const float b11 = be[ 0 ], b12 = be[ 4 ], b13 = be[ 8 ], b14 = be[ 12 ];
  const float b21 = be[ 1 ], b22 = be[ 5 ], b23 = be[ 9 ], b24 = be[ 13 ];
  const float b31 = be[ 2 ], b32 = be[ 6 ], b33 = be[ 10 ], b34 = be[ 14 ];
  const float b41 = be[ 3 ], b42 = be[ 7 ], b43 = be[ 11 ], b44 = be[ 15 ];

  te[ 0 ] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
  te[ 4 ] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
  te[ 8 ] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
  te[ 12 ] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

  te[ 1 ] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
  te[ 5 ] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
  te[ 9 ] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
  te[ 13 ] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

  te[ 2 ] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
  te[ 6 ] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
  te[ 10 ] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
  te[ 14 ] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

  te[ 3 ] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
  te[ 7 ] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
  te[ 11 ] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
  te[ 15 ] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;
}

void initShader() {
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
void blendWindow(int iEye, ID3D11ShaderResourceView *backbufferIn, ID3D11RenderTargetView *colorRenderTarget, ID3D11RenderTargetView *depthRenderTarget, ID3D11ShaderResourceView *depthIn) {
  HRESULT hr;

  // getOut() << "blend window" << std::endl;

  ID3D11ShaderResourceView *localShaderResourceViews[3] = {
    // windowResourceView,
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
  context->OMSetRenderTargets(
    ARRAYSIZE(localRenderTargetViews),
    localRenderTargetViews,
    nullptr
  );

  // pvrcompositor->InfoQueueLog();
  // getOut() << "do log 1" << std::endl;
  context->DrawIndexed(6, 0, 0);
  // pvrcompositor->InfoQueueLog();
  // getOut() << "do log 2" << std::endl;
  
  ID3D11ShaderResourceView *localShaderResourceViewsClear[ARRAYSIZE(localShaderResourceViews)] = {};
  context->PSSetShaderResources(0, ARRAYSIZE(localShaderResourceViewsClear), localShaderResourceViewsClear);
  ID3D11RenderTargetView *localRenderTargetViewsClear[ARRAYSIZE(localRenderTargetViews)] = {};
  context->OMSetRenderTargets(
    ARRAYSIZE(localRenderTargetViewsClear),
    localRenderTargetViewsClear,
    nullptr
  );
}
void homeRenderLoop() { 
  for (;;) {
    vr::TrackedDevicePose_t renderPoses[vr::k_unMaxTrackedDeviceCount];
    vr::TrackedDevicePose_t gamePoses[vr::k_unMaxTrackedDeviceCount];
    // getOut() << "wait 1" << std::endl;
    vr::g_pvrcompositor->WaitGetPoses(renderPoses, ARRAYSIZE(renderPoses), gamePoses, ARRAYSIZE(gamePoses));
    // getOut() << "wait 2" << std::endl;

    if (!device) {
      if (vr::g_pvrcompositor->device) {
        device = vr::g_pvrcompositor->device.Get();
        context = vr::g_pvrcompositor->context.Get();
        swapChain = vr::g_pvrcompositor->swapChain.Get();

        initShader();
      }
    }
    // getOut() << "wait 3 " << (void *)device << std::endl;
    if (device) {
      // getOut() << "wait 3 " << (void *)backbufferShHandle << std::endl;
      if (backbufferShHandle != backbufferShHandleLatched) {
        // getOut() << "wait 4" << std::endl;
        backbufferShHandleLatched = backbufferShHandle;

        if (backbufferShHandle) {
          ID3D11Resource *shTexResource;
          HRESULT hr = device->OpenSharedResource(backbufferShHandle, __uuidof(ID3D11Resource), (void**)(&shTexResource));

          if (SUCCEEDED(hr)) {
            hr = shTexResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&backbufferShTex));
            
            if (SUCCEEDED(hr)) {
              // nothing
            } else {
              getOut() << "failed to unpack backbuffer shared texture: " << (void *)hr << " " << (void *)backbufferShHandle << std::endl;
              abort();
            }
          } else {
            getOut() << "failed to unpack backbuffer shared texture handle: " << (void *)hr << " " << (void *)backbufferShHandle << std::endl;
            abort();
          }

          D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
          srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
          srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
          srvDesc.Texture2D.MostDetailedMip = 0;
          srvDesc.Texture2D.MipLevels = 1;

          hr = device->CreateShaderResourceView(
            backbufferShTex,
            &srvDesc,
            &backbufferShResourceView
          );
          if (SUCCEEDED(hr)) {
            // nothing
          } else {
            // InfoQueueLog();
            getOut() << "failed to create back buffer shader resource view: " << (void *)hr << std::endl;
            abort();
          }
        }
      }
      if (backbufferShHandle) {
        for (int iEye = 0; iEye < 2; iEye++) {
          blendWindow(
            iEye,
            backbufferShResourceView,
            vr::g_pvrcompositor->renderTargetViews[iEye],
            vr::g_pvrcompositor->renderTargetDepthBackViews[iEye],
            vr::g_pvrcompositor->depthShaderFrontResourceViews[iEye]
          );
          vr::g_pvrcompositor->SwapDepthTex(iEye);
          vr::g_pvrcompositor->Submit(iEye == 0 ? vr::Eye_Left : vr::Eye_Right, nullptr, nullptr, vr::EVRSubmitFlags::Submit_Default);
        }
      } else {
        vr::g_pvrcompositor->Submit(vr::Eye_Left, nullptr, nullptr, vr::EVRSubmitFlags::Submit_Default);
        vr::g_pvrcompositor->Submit(vr::Eye_Right, nullptr, nullptr, vr::EVRSubmitFlags::Submit_Default);
      }
    }
  }
}

}