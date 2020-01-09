// #include <chrono>
#include "device/vr/openvr/test/compositorproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRCompositor_SetTrackingSpace[] = "IVRCompositor::SetTrackingSpace";
char kIVRCompositor_GetTrackingSpace[] = "IVRCompositor::GetTrackingSpace";
char kIVRCompositor_WaitGetPoses[] = "IVRCompositor::WaitGetPoses";
char kIVRCompositor_GetLastPoses[] = "IVRCompositor::GetLastPoses";
char kIVRCompositor_GetLastPoseForTrackedDeviceIndex[] = "IVRCompositor::GetLastPoseForTrackedDeviceIndex";
char kIVRCompositor_PrepareSubmit[] = "IVRCompositor::PrepareSubmit";
char kIVRCompositor_Submit[] = "IVRCompositor::Submit";
char kIVRCompositor_FlushSubmit[] = "IVRCompositor::FlushSubmit";
char kIVRCompositor_ClearLastSubmittedFrame[] = "IVRCompositor::ClearLastSubmittedFrame";
char kIVRCompositor_PostPresentHandoff[] = "IVRCompositor::PostPresentHandoff";
char kIVRCompositor_GetFrameTiming[] = "IVRCompositor::GetFrameTiming";
char kIVRCompositor_GetFrameTimings[] = "IVRCompositor::GetFrameTimings";
char kIVRCompositor_GetFrameTimeRemaining[] = "IVRCompositor::GetFrameTimeRemaining";
char kIVRCompositor_GetCumulativeStats[] = "IVRCompositor::GetCumulativeStats";
char kIVRCompositor_FadeToColor[] = "IVRCompositor::FadeToColor";
char kIVRCompositor_GetCurrentFadeColor[] = "IVRCompositor::GetCurrentFadeColor";
char kIVRCompositor_FadeGrid[] = "IVRCompositor::FadeGrid";
char kIVRCompositor_GetCurrentGridAlpha[] = "IVRCompositor::GetCurrentGridAlpha";
char kIVRCompositor_ClearSkyboxOverride[] = "IVRCompositor::ClearSkyboxOverride";
char kIVRCompositor_CompositorBringToFront[] = "IVRCompositor::CompositorBringToFront";
char kIVRCompositor_CompositorGoToBack[] = "IVRCompositor::CompositorGoToBack";
char kIVRCompositor_CompositorQuit[] = "IVRCompositor::CompositorQuit";
char kIVRCompositor_IsFullscreen[] = "IVRCompositor::IsFullscreen";
char kIVRCompositor_GetCurrentSceneFocusProcess[] = "IVRCompositor::GetCurrentSceneFocusProcess";
char kIVRCompositor_GetLastFrameRenderer[] = "IVRCompositor::GetLastFrameRenderer";
char kIVRCompositor_CanRenderScene[] = "IVRCompositor::CanRenderScene";
char kIVRCompositor_ShowMirrorWindow[] = "IVRCompositor::ShowMirrorWindow";
char kIVRCompositor_HideMirrorWindow[] = "IVRCompositor::HideMirrorWindow";
char kIVRCompositor_IsMirrorWindowVisible[] = "IVRCompositor::IsMirrorWindowVisible";
char kIVRCompositor_CompositorDumpImages[] = "IVRCompositor::CompositorDumpImages";
char kIVRCompositor_ShouldAppRenderWithLowResources[] = "IVRCompositor::ShouldAppRenderWithLowResources";
char kIVRCompositor_ForceInterleavedReprojectionOn[] = "IVRCompositor::ForceInterleavedReprojectionOn";
char kIVRCompositor_ForceReconnectProcess[] = "IVRCompositor::ForceReconnectProcess";
char kIVRCompositor_SuspendRendering[] = "IVRCompositor::SuspendRendering";
char kIVRCompositor_GetMirrorTextureD3D11[] = "IVRCompositor::GetMirrorTextureD3D11";
char kIVRCompositor_ReleaseMirrorTextureD3D11[] = "IVRCompositor::ReleaseMirrorTextureD3D11";
char kIVRCompositor_GetMirrorTextureGL[] = "IVRCompositor::GetMirrorTextureGL";
char kIVRCompositor_ReleaseSharedGLTexture[] = "IVRCompositor::ReleaseSharedGLTexture";
char kIVRCompositor_LockGLSharedTextureForAccess[] = "IVRCompositor::LockGLSharedTextureForAccess";
char kIVRCompositor_UnlockGLSharedTextureForAccess[] = "IVRCompositor::UnlockGLSharedTextureForAccess";
char kIVRCompositor_GetVulkanInstanceExtensionsRequired[] = "IVRCompositor::GetVulkanInstanceExtensionsRequired";
char kIVRCompositor_GetVulkanDeviceExtensionsRequired[] = "IVRCompositor::GetVulkanDeviceExtensionsRequired";
char kIVRCompositor_SetExplicitTimingMode[] = "IVRCompositor::SetExplicitTimingMode";
char kIVRCompositor_SubmitExplicitTimingData[] = "IVRCompositor::SubmitExplicitTimingData";
char kIVRCompositor_IsMotionSmoothingEnabled[] = "IVRCompositor::IsMotionSmoothingEnabled";
char kIVRCompositor_IsMotionSmoothingSupported[] = "IVRCompositor::IsMotionSmoothingSupported";
char kIVRCompositor_IsCurrentSceneFocusAppLoading[] = "IVRCompositor::IsCurrentSceneFocusAppLoading";

const char *composeVsh = ""
"#version 330\n\
\n\
in vec2 position;\n\
in vec2 uv;\n\
out vec2 vUv;\n\
\n\
void main() {\n\
  vUv = uv;\n\
  gl_Position = vec4(position.xy, 0., 1.);\n\
}\n\
";
const char *composeFsh = ""
"#version 330\n\
\n\
in vec2 vUv;\n\
out vec4 fragColor;\n\
uniform sampler2D tex1;\n\
uniform sampler2D tex2;\n\
uniform float hasTex1;\n\
uniform float hasTex2;\n\
uniform vec4 texBounds1;\n\
uniform vec4 texBounds2;\n\
// uniform  sampler2D depthTex;\n\
\n\
void main() {\n\
  if (hasTex1 > 0.0) {\n\
    vec4 c = texture(tex1, texBounds1.xy + vUv * (texBounds1.zw - texBounds1.xy));\n\
    fragColor += vec4(c.rgb*c.a, c.a);\n\
  }\n\
  if (hasTex2 > 0.0) {\n\
    vec4 c = texture(tex2, texBounds2.xy + vUv * (texBounds2.zw - texBounds2.xy));\n\
    fragColor += vec4(c.rgb*c.a, c.a);\n\
  }\n\
  // if (fragColor.a < 0.5) discard;\n\
  // fragColor = vec4(vec3(0.0), 1.0);\n\
  // fragColor.r += 0.1;\n\
  // gl_FragDepth = texture(depthTex, vUv).r;\n\
}\n\
";
const char *blitFsh = ""
"#version 330\n\
\n\
in vec2 vUv;\n\
out vec4 fragColor;\n\
uniform sampler2D tex;\n\
\n\
void main() {\n\
  fragColor = vec4(texture(tex, vUv).rgb, 1.0);\n\
  // fragColor += vec4(0.5, 0.0, 0.0, 0.1);\n\
}\n\
";
constexpr size_t MAX_LAYERS = 2;
const EVREye EYES[] = {
  Eye_Left,
  Eye_Right,
};

/* void checkError(const char *label) {
  auto error = glGetError();
  if (error) {
    getOut() << "gl error: " << error << " " << label << std::endl;
  }
} */

PVRCompositor::PVRCompositor(IVRCompositor *vrcompositor, FnProxy &fnp) :
  vrcompositor(vrcompositor),
  fnp(fnp)
{
  fnp.reg<
    kIVRCompositor_SetTrackingSpace,
    int,
    ETrackingUniverseOrigin
  >([=](ETrackingUniverseOrigin eOrigin) {
    vrcompositor->SetTrackingSpace(eOrigin);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetTrackingSpace,
    ETrackingUniverseOrigin
  >([=]() {
    return vrcompositor->GetTrackingSpace();
  });
  fnp.reg<
    kIVRCompositor_WaitGetPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
    // getOut() << "waitgetposes 1" << std::endl;
    managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
    managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);
    // getOut() << "handle poses 2" << std::endl;

    memcpy(renderPoseArray.data(), cachedRenderPoses, unRenderPoseArrayCount * sizeof(TrackedDevicePose_t));
    memcpy(gamePoseArray.data(), cachedGamePoses, unGamePoseArrayCount * sizeof(TrackedDevicePose_t));

    // EVRCompositorError error = vrcompositor->WaitGetPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);

    // getOut() << "handle poses 3" << std::endl;

    EVRCompositorError error = VRCompositorError_None;
    auto result = std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(renderPoseArray),
      std::move(gamePoseArray)
    );
    // getOut() << "handle poses 4" << std::endl;
    return std::move(result);
  });
  fnp.reg<
    kIVRCompositor_GetLastPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >([=](uint32_t unRenderPoseArrayCount, uint32_t unGamePoseArrayCount) {
    managed_binary<TrackedDevicePose_t> renderPoseArray(unRenderPoseArrayCount);
    managed_binary<TrackedDevicePose_t> gamePoseArray(unGamePoseArrayCount);

    memcpy(renderPoseArray.data(), cachedRenderPoses, unRenderPoseArrayCount * sizeof(TrackedDevicePose_t));
    memcpy(gamePoseArray.data(), cachedGamePoses, unGamePoseArrayCount * sizeof(TrackedDevicePose_t));

    // auto start = std::chrono::high_resolution_clock::now();
    // EVRCompositorError error = vrcompositor->GetLastPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);
    /* auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    getOut() << "get last poses real " << elapsed.count() << std::endl; */

    return std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(renderPoseArray),
      std::move(gamePoseArray)
    );
  });
  fnp.reg<
    kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    TrackedDeviceIndex_t
  >([=](TrackedDeviceIndex_t unDeviceIndex) {
    managed_binary<TrackedDevicePose_t> outputPose(1);
    managed_binary<TrackedDevicePose_t> gamePose(1);

    EVRCompositorError error = vrcompositor->GetLastPoseForTrackedDeviceIndex(unDeviceIndex, outputPose.data(), gamePose.data());

    return std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>(
      error,
      std::move(outputPose),
      std::move(gamePose)
    );
  });
  fnp.reg<
    kIVRCompositor_PrepareSubmit,
    int,
    ETextureType
  >([=](ETextureType textureType) {
    // getOut() << "prepare submit server 1" << std::endl;

    if (!device) {
      // device = (ID3D11Device *)pDevice;

      int32_t adapterIndex;
      g_vrsystem->GetDXGIOutputInfo(&adapterIndex);
      if (adapterIndex == -1) {
        adapterIndex = 0;
      }

      Microsoft::WRL::ComPtr<IDXGIFactory1> dxgi_factory;
      IDXGIAdapter1 *adapter;
      HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), &dxgi_factory);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "create dxgi factory failed " << (void *)hr << std::endl;
      }
      dxgi_factory->EnumAdapters1(adapterIndex, &adapter);

      getOut() << "create device " << adapterIndex << " " << (void *)adapter << std::endl;

      for (unsigned int i = 0;; i++) {
        hr = dxgi_factory->EnumAdapters1(i, &adapter);
        if (SUCCEEDED(hr)) {
          DXGI_ADAPTER_DESC desc;
          adapter->GetDesc(&desc);
          getOut() << "got adapter desc " << i << (char *)desc.Description << " " << desc.AdapterLuid.HighPart << " " << desc.AdapterLuid.LowPart << std::endl;
        } else {
          break;
        }
      }
      
      // getOut() << "creating device 1" << std::endl;

      // Microsoft::WRL::ComPtr<ID3D11Device> device;
      // Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
      Microsoft::WRL::ComPtr<ID3D11Device> deviceBasic;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext> contextBasic;
      D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1
      };
      hr = D3D11CreateDevice(
        // NULL, // pAdapter
        adapter, // pAdapter
        D3D_DRIVER_TYPE_HARDWARE, // DriverType
        NULL, // Software
        0, // Flags
        featureLevels, // pFeatureLevels
        ARRAYSIZE(featureLevels), // FeatureLevels
        D3D11_SDK_VERSION, // SDKVersion
        &deviceBasic, // ppDevice
        NULL, // pFeatureLevel
        &contextBasic // ppImmediateContext
      );
      // getOut() << "creating device 2" << std::endl;
      if (SUCCEEDED(hr)) {
        hr = deviceBasic->QueryInterface(__uuidof(ID3D11Device5), (void **)&device);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "device query failed" << std::endl;
          abort();
        }
        
        Microsoft::WRL::ComPtr<ID3D11DeviceContext3> context3;
        device->GetImmediateContext3(&context3);
        hr = context3->QueryInterface(__uuidof(ID3D11DeviceContext4), (void **)&context);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "context query failed" << std::endl;
          abort();
        }
        
        /* hr = contextBasic->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&context);
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "context query failed" << std::endl;
        } */
        
        IDXGIDevice * pDXGIDevice = nullptr;
        hr = device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
        
        IDXGIAdapter * pDXGIAdapter = nullptr;
        hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
        
        DXGI_ADAPTER_DESC desc;
        hr = pDXGIAdapter->GetDesc(&desc);
        getOut() << "got desc " << (char *)desc.Description << " " << desc.AdapterLuid.HighPart << " " << desc.AdapterLuid.LowPart << std::endl;
        
        // nothing
      } else {
        getOut() << "create dx device failed " << (void *)hr << std::endl;
        abort();
      }

      subWindow = initGl();

      // getOut() << "prepare submit server 4 " << (void *)device.Get() << std::endl;

      // getOut() << "gl init 1 " << (void *)subWindow << " " << (void *)device.Get() << " " << glGetError() << std::endl;

      // getOut() << "open interop device 1 " << (void *)device.Get() << std::endl;

      hInteropDevice = wglDXOpenDeviceNV(device.Get());
      
      // getOut() << "open interop device 2 " << (void *)hInteropDevice << std::endl;

      // getOut() << "prepare submit server 5" << std::endl;

      // getOut() << "gl init 2 " << (void *)hInteropDevice << " " << glGetError() << std::endl;
      
      GLuint vao;
      glGenVertexArrays(1, &vao);
      glBindVertexArray(vao);
      
      // getOut() << "prepare submit server 6" << std::endl;
      
      // getOut() << "gl init 3 " << glGetError() << std::endl;

      GLuint textures[4];
      glGenTextures(ARRAYSIZE(textures), textures);
      shTexOutIds.resize(2);
      shTexOutIds[0] = textures[0];
      shTexOutIds[1] = textures[1];
      texDepthIds.resize(2);
      texDepthIds[0] = textures[2];
      texDepthIds[1] = textures[3];
      
      // getOut() << "getting width height" << std::endl;
      
      // getOut() << "prepare submit server 7" << std::endl;

      // getOut() << "gl init 4 " << glGetError() << std::endl;

      // glBindTexture(GL_TEXTURE_2D, shTexOutId);
      // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      g_vrsystem->GetRecommendedRenderTargetSize(&width, &height);
      getOut() << "got width height backend " << width << " " << height << std::endl;
      glBindTexture(GL_TEXTURE_2D, texDepthIds[0]);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
      glBindTexture(GL_TEXTURE_2D, texDepthIds[1]);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
      glBindTexture(GL_TEXTURE_2D, 0);
      
      // getOut() << "prepare submit server 8" << std::endl;
      
      // getOut() << "gl init 5 " << glGetError() << std::endl;
      
      D3D11_TEXTURE2D_DESC desc{};
      desc.Width = width;
      desc.Height = height;
      desc.ArraySize = 1;
      desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      // desc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
      desc.SampleDesc.Count = 1;
      desc.Usage = D3D11_USAGE_DEFAULT;
      // desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
      // desc.BindFlags = 40; // D3D11_BIND_DEPTH_STENCIL
      desc.BindFlags = 0; // D3D11_BIND_DEPTH_STENCIL
      // desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;
      // desc.MiscFlags = 0; 
      // getOut() << "gl init 6 " << width << " " << height << " " << (void *)device.Get() << " " << glGetError() << std::endl;
      /* getOut() << "get texture desc back " << (int)eEye << " " << desc.Width << " " << desc.Height << " " <<
        pBounds->uMin << " " << pBounds->vMin << " " <<
        pBounds->uMax << " " << pBounds->vMax << " " <<
        std::endl; */
      shTexOuts.resize(2);
      shTexOutInteropHandles.resize(2);
      // getOut() << "interop 1" << std::endl;
      for (int i = 0; i < 2; i++) {
        HRESULT hr = device->CreateTexture2D(
          &desc,
          NULL,
          &shTexOuts[i]
        );
        shTexOutInteropHandles[i] = wglDXRegisterObjectNV(hInteropDevice, shTexOuts[i], shTexOutIds[i], GL_TEXTURE_2D, WGL_ACCESS_WRITE_DISCARD_NV);
      }
      // getOut() << "interop 2" << std::endl;
      
      // getOut() << "prepare submit server 9" << std::endl;
      
      /* if (!shTexOutInteropHandle) {
        getOut() << "gl init error 1 " << (void *)shTexOutInteropHandle << " " << (void *)hr << " " << (void *)shTexOut << " " << (void *)shTexOutId << " " << glGetError() << std::endl;
        abort();
      } */

      // vertex shader
      GLuint composeVertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(composeVertex, 1, &composeVsh, NULL);
      glCompileShader(composeVertex);
      GLint success;
      glGetShaderiv(composeVertex, GL_COMPILE_STATUS, &success);
      if (!success) {
        char infoLog[4096];
        GLsizei length;
        glGetShaderInfoLog(composeVertex, sizeof(infoLog), &length, infoLog);
        infoLog[length] = '\0';
        getOut() << "compose vertex shader compilation failed:\n" << infoLog << std::endl;
        abort();
      };
      
      getOut() << "prepare submit server 10" << std::endl;

      // getOut() << "gl init error 2 " << glGetError() << std::endl;

      // fragment shader
      GLuint composeFragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(composeFragment, 1, &composeFsh, NULL);
      glCompileShader(composeFragment);
      glGetShaderiv(composeFragment, GL_COMPILE_STATUS, &success);
      if (!success) {
        char infoLog[4096];
        GLsizei length;
        glGetShaderInfoLog(composeFragment, sizeof(infoLog), &length, infoLog);
        infoLog[length] = '\0';
        getOut() << "compose fragment shader compilation failed:\n" << infoLog << std::endl;
        abort();
      };
      
      // getOut() << "prepare submit server 11" << std::endl;
      
      // getOut() << "gl init error 3 " << glGetError() << std::endl;

      // shader program
      GLuint composeProgram = glCreateProgram();
      glAttachShader(composeProgram, composeVertex);
      glAttachShader(composeProgram, composeFragment);
      glLinkProgram(composeProgram);
      glGetProgramiv(composeProgram, GL_LINK_STATUS, &success);
      if (!success) {
        char infoLog[4096];
        GLsizei length;
        glGetShaderInfoLog(composeProgram, sizeof(infoLog), &length, infoLog);
        infoLog[length] = '\0';
        getOut() << "compose program linking failed\n" << infoLog << std::endl;
        abort();
      }
      
      // getOut() << "prepare submit server 12" << std::endl;
      
      // getOut() << "gl init error 4 " << glGetError() << std::endl;

      GLuint positionLocation = glGetAttribLocation(composeProgram, "position");
      if (positionLocation == -1) {
        getOut() << "compose program failed to get attrib location for 'position'" << std::endl;
        abort();
      }
      // getOut() << "prepare submit server 13" << std::endl;
      GLuint uvLocation = glGetAttribLocation(composeProgram, "uv");
      if (uvLocation == -1) {
        getOut() << "compose program failed to get attrib location for 'uv'" << std::endl;
        abort();
      }
      // getOut() << "prepare submit server 14" << std::endl;
      texLocations.resize(MAX_LAYERS);
      hasTexLocations.resize(MAX_LAYERS);
      texBoundsLocations.resize(MAX_LAYERS);
      for (size_t i = 0; i < MAX_LAYERS; i++) {
        std::string texString = std::string("tex") + std::to_string(i+1);
        GLuint texLocation = glGetUniformLocation(composeProgram, texString.c_str());
        // getOut() << "get location 1  " << texString << " " << texLocation << std::endl;
        if (texLocation != -1) {
          texLocations[i] = texLocation;
        } else {
          getOut() << "compose program failed to get uniform location for '" << texString << "'" << std::endl;
          abort();
        }

        std::string hasTexString = std::string("hasTex") + std::to_string(i+1);
        GLuint hasTexLocation = glGetUniformLocation(composeProgram, hasTexString.c_str());
        // getOut() << "get location 2 " << hasTexString << " " << hasTexLocation << std::endl;
        if (hasTexLocation != -1) {
          hasTexLocations[i] = hasTexLocation;
        } else {
          getOut() << "compose program failed to get uniform location for '" << hasTexString << "'" << std::endl;
          abort();
        }

        std::string texBoundsString = std::string("texBounds") + std::to_string(i+1);
        GLuint texBoundsLocation = glGetUniformLocation(composeProgram, texBoundsString.c_str());
        // getOut() << "get location 2 " << hasTexString << " " << hasTexLocation << std::endl;
        if (texBoundsLocation != -1) {
          texBoundsLocations[i] = texBoundsLocation;
        } else {
          getOut() << "compose program failed to get uniform location for '" << texBoundsString << "'" << std::endl;
          abort();
        }
      }
      // getOut() << "prepare submit server 15" << std::endl;
      /* GLuint depthTexLocation = glGetUniformLocation(composeProgram, "depthTex");
      if (depthTexLocation == -1) {
        getOut() << "compose program failed to get uniform location for 'depthTex'" << std::endl;
        abort();
      } */

      // getOut() << "gl init error 5 " << glGetError() << std::endl;

      // delete the shaders as they're linked into our program now and no longer necessary
      glDeleteShader(composeVertex);
      glDeleteShader(composeFragment);

      glUseProgram(composeProgram);

      GLuint positionBuffer;
      glGenBuffers(1, &positionBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
      static const float positions[] = {
        -1.0f, 1.0f,
        1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f,
      };
      glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
      glEnableVertexAttribArray(positionLocation);
      glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, 0);

      // getOut() << "gl init error 6 " << glGetError() << std::endl;

      GLuint uvBuffer;
      glGenBuffers(1, &uvBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
      static const float uvs[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
      };
      glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
      glEnableVertexAttribArray(uvLocation);
      glVertexAttribPointer(uvLocation, 2, GL_FLOAT, false, 0, 0);

      // getOut() << "gl init error 7 " << glGetError() << std::endl;

      GLuint indexBuffer;
      glGenBuffers(1, &indexBuffer);
      static const uint16_t indices[] = {0, 2, 1, 2, 3, 1};
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
      
      /* glActiveTexture(GL_TEXTURE0);
      glUniform1i(tex1Location, 0);
      glActiveTexture(GL_TEXTURE0);
      glUniform1i(tex2Location, 1); */
      for (size_t i = 0; i < MAX_LAYERS; i++) {
        if (texLocations[i] != -1) {
          glUniform1i(texLocations[i], i);
        }
      }

      fbos.resize(2);
      glGenFramebuffers(fbos.size(), fbos.data());

      glViewport(0, 0, width, height);      
      // glEnable(GL_SCISSOR_TEST);
      glClearColor(0, 0, 0, 0);
      
      // getOut() << "prepare submit server 16" << std::endl;
    }
    
    // getOut() << "interop 3" << std::endl;
    
    // getOut() << "prepare submit server 20" << std::endl;

    // return fenceHandle;
    return 0;
  });
  fnp.reg<
    kIVRCompositor_Submit,
    EVRCompositorError,
    EVREye,
    managed_binary<Texture_t>,
    managed_binary<VRTextureBounds_t>,
    EVRSubmitFlags
  >([=, &fnp](EVREye eEye, managed_binary<Texture_t> sharedTexture, managed_binary<VRTextureBounds_t> bounds, EVRSubmitFlags submitFlags) {
    Texture_t *pTexture = sharedTexture.data();
    VRTextureBounds_t *pBounds = bounds.data();

    getOut() << "submit server " << fnp.remoteProcessId << " " << (int)eEye << std::endl;

    auto key = std::pair<size_t, EVREye>(fnp.remoteProcessId, eEye);
    auto iter = inBackIndices.find(key);
    size_t index;
    if (iter != inBackIndices.end()) {
      index = iter->second;
    } else {
      index = inBackTexs.size();
      inBackIndices[key] = index;
      iter = inBackIndices.find(key);

      inBackTexs.resize(index+1, NULL);
      inBackInteropHandles.resize(index+1, NULL);
      inBackReadEvents.resize(index+1, NULL);
      inBackTextureBounds.resize(index+1, VRTextureBounds_t{});
      inBackHandleLatches.resize(index+1, NULL);
    }
    
    // getOut() << "submit server 2" << std::endl;

    HANDLE sharedHandle = (HANDLE)pTexture->handle;
    GLuint &shTexInId = inBackTexs[index]; // gl texture
    HANDLE &shTexInInteropHandle = inBackInteropHandles[index]; // interop texture handle
    HANDLE &readEvent = inBackReadEvents[index]; // interop texture handle
    VRTextureBounds_t &textureBounds = inBackTextureBounds[index]; // interop texture handle
    HANDLE &handleLatched = inBackHandleLatches[index]; // remembered attachemnt

    // getOut() << "submit server 3" << std::endl;

    if (handleLatched != sharedHandle) {
      // getOut() << "got shTex in " << (void *)sharedHandle << std::endl;
      if (handleLatched) {
        // glDeleteTextures(1, &shTexInId);
        // XXX delete old resources
        // hr = device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&pD3DResource));
      }
      handleLatched = sharedHandle;

      // getOut() << "submit server 4" << std::endl;

      // IDXGIResource1 *pD3DResource;
      // HRESULT hr = device->OpenSharedResource1(sharedHandle, __uuidof(IDXGIResource1), (void**)(&pD3DResource));
      ID3D11Resource *shTexResource;
      HRESULT hr = device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&shTexResource));

      // getOut() << "submit server 5" << std::endl;

      ID3D11Texture2D *shTexIn;
      if (SUCCEEDED(hr)) {
        hr = shTexResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&shTexIn));
        
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to unpack shared texture: " << (void *)hr << " " << (void *)sharedHandle << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to unpack shared texture handle: " << (void *)hr << " " << (void *)sharedHandle << std::endl;
        abort();
      }
    
      // getOut() << "submit server 6 " << GetLastError() << std::endl;

      glGenTextures(1, &shTexInId);
      shTexInInteropHandle = wglDXRegisterObjectNV(hInteropDevice, shTexIn, shTexInId, GL_TEXTURE_2D, WGL_ACCESS_READ_ONLY_NV);
      if (shTexInInteropHandle) {
        // nothing
      } else {
        // C007006E
        getOut() << "failed to get shared interop handle " << (void *)hInteropDevice << " " << shTexIn << " " << shTexInId << " " << glGetError() << " " << GetLastError() << std::endl;
        abort();
      }
      shTexIn->Release();
      shTexResource->Release();
      
      getOut() << "open backend event " << (std::string("Local\\OpenVrFenceEvent") + std::to_string(std::get<0>(key)) + std::string(":") + std::to_string((int)std::get<1>(key))) << std::endl;
      readEvent = OpenEventA(
        GENERIC_ALL,
        false,
        (std::string("Local\\OpenVrFenceEvent") + std::to_string(std::get<0>(key)) + std::string(":") + std::to_string((int)std::get<1>(key))).c_str()
      );
      
      if (!readEvent) {
        getOut() << "failed to open backend read event" << std::endl;
        abort();
      }

      // getOut() << "submit server 7 " << (void *)readEvent << std::endl;
    }

    textureBounds = *pBounds;

    inBackReadEventQueue.push_back(std::tuple<EVREye, uint64_t, HANDLE>(eEye, fnp.remoteProcessId, readEvent));

    /* if (!fence) {
      ID3D11Resource *fenceResource;
      HRESULT hr = device->OpenSharedResource(fenceHandle, __uuidof(ID3D11Resource), (void**)(&fenceResource));

      getOut() << "submit server 8" << std::endl;

      if (SUCCEEDED(hr)) {
        hr = fenceResource->QueryInterface(__uuidof(ID3D11Fence), (void**)(&fence));
        
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to unpack shared fence: " << (void *)hr << " " << (void *)fenceHandle << std::endl;
          abort();
        }
      } else {
        getOut() << "failed to unpack shared fence handle: " << (void *)hr << " " << (void *)fenceHandle << std::endl;
        abort();
      }
    } */

    // getOut() << "submit server 9 " << (void *)readEvent << std::endl;

    // auto r = WaitForSingleObject(readEvent, INFINITE);
    // ++fenceValue;
    // context->Wait(fence.Get(), fenceValue);
    
    // getOut() << "submit server 9" << std::endl;

    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_FlushSubmit,
    int
  >([=]() {
    // getOut() << "flush submit server 1" << std::endl;

for (int iEye = 0; iEye < ARRAYSIZE(EYES); iEye++) {
    EVREye eEye = EYES[iEye];
    
    // getOut() << "flush submit server 2" << std::endl;

    for (auto iter : inBackReadEventQueue) {
      EVREye &e = std::get<0>(iter);
      if (e == eEye) {
        getOut() << "wait for read pre " << (std::to_string(std::get<0>(iter)) + std::string(":") + std::to_string((int)std::get<1>(iter))) << std::endl;
        HANDLE &readEvent = std::get<2>(iter);
        WaitForSingleObject(readEvent, INFINITE);
        getOut() << "wait for read post " << (std::to_string(std::get<0>(iter)) + std::string(":") + std::to_string((int)std::get<1>(iter))) << std::endl;
      }
    }

    std::vector<HANDLE> objects;
    objects.reserve(inBackIndices.size()/2 + 1);
    for (auto iter : inBackIndices) {
      EVREye e = iter.first.second;
      if (e == eEye) {
        size_t index = iter.second;
        HANDLE h = inBackInteropHandles[index];
        objects.push_back(h);
        // getOut() << "got handle " << (void *)h << std::endl;
      }
    }
    objects.push_back(shTexOutInteropHandles[iEye]);
    // getOut() << "got handle end " << (void *)shTexOutInteropHandles[iEye] << std::endl;
    
    // getOut() << "flush submit server 2 " << " " << (void *)hInteropDevice << std::endl;

    bool lockOk = wglDXLockObjectsNV(hInteropDevice, objects.size(), objects.data());
    // getOut() << "gl init error 11 " << lockOk << " " << glGetError() << std::endl;
    if (lockOk) {
      // getOut() << "flush submit server 3 " << (int)eye << std::endl;

      // checkError("flush submit server 3");

      size_t numLayers = 0;
      for (auto iter : inBackIndices) {
        EVREye e = iter.first.second;
        if (e == eEye) {
          size_t &index = iter.second;

          glActiveTexture(GL_TEXTURE0 + numLayers);
          glBindTexture(GL_TEXTURE_2D, inBackTexs[index]);
          glUniform1f(hasTexLocations[numLayers], 1.0f);
          const VRTextureBounds_t &textureBounds = inBackTextureBounds[index];
          glUniform4f(texBoundsLocations[numLayers], textureBounds.uMin, textureBounds.vMin, textureBounds.uMax, textureBounds.vMax);

          numLayers++;
          if (numLayers >= MAX_LAYERS) {
            break;
          }
        }
      }
      // checkError("flush submit server 4");
      for (size_t i = numLayers; i < MAX_LAYERS; i++) {
        // glActiveTexture(GL_TEXTURE0 + i);
        // glBindTexture(GL_TEXTURE_2D, 0);
        glUniform1f(hasTexLocations[i], 0.0f);
        // glUniform4f(texBoundsLocations[i], 0.0f, 0.0f, 1.0f, 1.0f);
      }
      
      // checkError("flush submit server 5");

      glBindFramebuffer(GL_FRAMEBUFFER, fbos[iEye]);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shTexOutIds[iEye], 0);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texDepthIds[iEye], 0);
      // auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

      glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_SHORT,
        (void *)0
      );
      // checkError("flush submit server 6");

      // getOut() << "flush submit server 6 " << (int)eye << std::endl;

      // getOut() << "gl submit 1 " << glGetError() << std::endl;
      // pTexture->handle = (void *)shTexOut;
      // getOut() << "flush submit server 8" << std::endl;
      // getOut() << "flush submit server 9" << std::endl;
      bool unlockOk = wglDXUnlockObjectsNV(hInteropDevice, objects.size(), objects.data());
      // checkError("flush submit server 7");
      if (unlockOk) {
        // nothing
        // EVREye eye = EYES[iEye];
        Texture_t texture{
          (void *)shTexOuts[iEye],
          TextureType_DirectX,
          ColorSpace_Auto
        };
        VRTextureBounds_t bounds{
          0.0f, 0.0f,
          1.0f, 1.0f
        };
        // getOut() << "flush submit server 7 " << (int)eye << std::endl;
        // getOut() << "gl submit 2 " << glGetError() << std::endl;
        auto result = vrcompositor->Submit(eEye, &texture, &bounds, EVRSubmitFlags::Submit_Default);
        // getOut() << "compositor submit result " << (void *)result << std::endl;
      } else {
        getOut() << "texture unlocking failed" << std::endl;
        abort();
      }
    } else {
      getOut() << "texture locking failed" << std::endl;
      abort();
    }
    // vrcompositor->PostPresentHandoff();
}

    // getOut() << "flush submit server 10 " << inBackReadEventQueue.size() << std::endl;

    inBackReadEventQueue.clear();

    // getOut() << "flush submit server 11" << std::endl;
    return 0;
  });
  fnp.reg<
    kIVRCompositor_ClearLastSubmittedFrame,
    int
  >([=]() {
    vrcompositor->ClearLastSubmittedFrame();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_PostPresentHandoff,
    int
  >([=]() {
    // getOut() << "post present handoff server 1" << std::endl;
    vrcompositor->PostPresentHandoff();
    // getOut() << "post present handoff server 2" << std::endl;
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetFrameTiming,
    std::tuple<bool, managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >([=](uint32_t unFramesAgo) {
    getOut() << "server get frame timing 1" << std::endl;
    managed_binary<Compositor_FrameTiming> timing(1);
    bool result = vrcompositor->GetFrameTiming(timing.data(), unFramesAgo);
    getOut() << "server get frame timing 2" << std::endl;
    return std::tuple<bool, managed_binary<Compositor_FrameTiming>>(
      result,
      std::move(timing)
    );
  });
  fnp.reg<
    kIVRCompositor_GetFrameTimings,
    std::tuple<uint32_t, managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >([=](uint32_t nFrames) {
    managed_binary<Compositor_FrameTiming> timings(nFrames);
    uint32_t result = vrcompositor->GetFrameTimings(timings.data(), nFrames);
    return std::tuple<uint32_t, managed_binary<Compositor_FrameTiming>>(
      result,
      std::move(timings)
    );
  });
  fnp.reg<
    kIVRCompositor_GetFrameTimeRemaining,
    float
  >([=]() {
    return vrcompositor->GetFrameTimeRemaining();
  });
  fnp.reg<
    kIVRCompositor_GetCumulativeStats,
    managed_binary<Compositor_CumulativeStats>,
    uint32_t
  >([=](uint32_t nStatsSizeInBytes) {
    managed_binary<Compositor_CumulativeStats> stats(1);

    vrcompositor->GetCumulativeStats(stats.data(), nStatsSizeInBytes);

    return std::move(stats);
  });
  fnp.reg<
    kIVRCompositor_FadeToColor,
    int,
    float,
    float,
    float,
    float,
    float,
    bool
  >([=](float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground) {
    vrcompositor->FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetCurrentFadeColor,
    managed_binary<HmdColor_t>,
    bool
  >([=](bool bBackground) {
    managed_binary<HmdColor_t> result(1);

    *result.data() = vrcompositor->GetCurrentFadeColor(bBackground);
    
    return std::move(result);
  });
  fnp.reg<
    kIVRCompositor_FadeGrid,
    int,
    float,
    bool
  >([=](float fSeconds, bool bFadeIn) {
    vrcompositor->FadeGrid(fSeconds, bFadeIn);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetCurrentGridAlpha,
    float
  >([=]() {
    return vrcompositor->GetCurrentGridAlpha();
  });
  fnp.reg<
    kIVRCompositor_ClearSkyboxOverride,
    int
  >([=]() {
    vrcompositor->ClearSkyboxOverride();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_CompositorBringToFront,
    int
  >([=]() {
    vrcompositor->CompositorBringToFront();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_CompositorGoToBack,
    int
  >([=]() {
    vrcompositor->CompositorGoToBack();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_CompositorQuit,
    int
  >([=]() {
    vrcompositor->CompositorQuit();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_IsFullscreen,
    bool
  >([=]() {
    return vrcompositor->IsFullscreen();
  });
  fnp.reg<
    kIVRCompositor_GetCurrentSceneFocusProcess,
    uint32_t
  >([=]() {
    return vrcompositor->GetCurrentSceneFocusProcess();
  });
  fnp.reg<
    kIVRCompositor_GetLastFrameRenderer,
    uint32_t
  >([=]() {
    return vrcompositor->GetLastFrameRenderer();
  });
  fnp.reg<
    kIVRCompositor_CanRenderScene,
    bool
  >([=]() {
    return vrcompositor->CanRenderScene();
  });
  fnp.reg<
    kIVRCompositor_ShowMirrorWindow,
    int
  >([=]() {
    vrcompositor->ShowMirrorWindow();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_HideMirrorWindow,
    int
  >([=]() {
    vrcompositor->HideMirrorWindow();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_IsMirrorWindowVisible,
    bool
  >([=]() {
    return vrcompositor->IsMirrorWindowVisible();
  });
  fnp.reg<
    kIVRCompositor_CompositorDumpImages,
    int
  >([=]() {
    vrcompositor->CompositorDumpImages();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_ShouldAppRenderWithLowResources,
    bool
  >([=]() {
    return vrcompositor->ShouldAppRenderWithLowResources();
  });
  fnp.reg<
    kIVRCompositor_ForceInterleavedReprojectionOn,
    int,
    bool
  >([=](bool bOverride) {
    vrcompositor->ForceInterleavedReprojectionOn(bOverride);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_ForceReconnectProcess,
    int
  >([=]() {
    getOut() << "ForceReconnectProcess" << std::endl;
    abort();
    // vrcompositor->ForceReconnectProcess();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_SuspendRendering,
    int,
    bool
  >([=](bool bSuspend) {
    vrcompositor->SuspendRendering(bSuspend);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetMirrorTextureD3D11,
    vr::EVRCompositorError
  >([=]() {
    getOut() << "GetMirrorTextureD3D11" << std::endl;
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_ReleaseMirrorTextureD3D11,
    vr::EVRCompositorError
  >([=]() {
    getOut() << "ReleaseMirrorTextureD3D11" << std::endl;
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_GetMirrorTextureGL,
    vr::EVRCompositorError
  >([=]() {
    getOut() << "GetMirrorTextureGL" << std::endl;
    abort();
    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_ReleaseSharedGLTexture,
    bool
  >([=]() {
    getOut() << "ReleaseSharedGLTexture" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_LockGLSharedTextureForAccess,
    bool
  >([=]() {
    getOut() << "LockGLSharedTextureForAccess" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_UnlockGLSharedTextureForAccess,
    bool
  >([=]() {
    getOut() << "UnlockGLSharedTextureForAccess" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_GetVulkanInstanceExtensionsRequired,
    uint32_t
  >([=]() {
    getOut() << "GetVulkanInstanceExtensionsRequired" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_GetVulkanDeviceExtensionsRequired,
    uint32_t
  >([=]() {
    getOut() << "GetVulkanDeviceExtensionsRequired" << std::endl;
    abort();
    return false;
  });
  fnp.reg<
    kIVRCompositor_SetExplicitTimingMode,
    int,
    EVRCompositorTimingMode
  >([=](EVRCompositorTimingMode eTimingMode) {
    vrcompositor->SetExplicitTimingMode(eTimingMode);
    return 0;
  });
  fnp.reg<
    kIVRCompositor_SubmitExplicitTimingData,
    EVRCompositorError
  >([=]() {
    return vrcompositor->SubmitExplicitTimingData();
  });
  fnp.reg<
    kIVRCompositor_IsMotionSmoothingEnabled,
    bool
  >([=]() {
    return vrcompositor->IsMotionSmoothingEnabled();
  });
  fnp.reg<
    kIVRCompositor_IsMotionSmoothingSupported,
    bool
  >([=]() {
    return vrcompositor->IsMotionSmoothingSupported();
  });
  fnp.reg<
    kIVRCompositor_IsCurrentSceneFocusAppLoading,
    bool
  >([=]() {
    return vrcompositor->IsCurrentSceneFocusAppLoading();
  });
}
void PVRCompositor::SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) {
  fnp.call<kIVRCompositor_SetTrackingSpace, int, ETrackingUniverseOrigin>(eOrigin);
}
ETrackingUniverseOrigin PVRCompositor::GetTrackingSpace() {
  return fnp.call<kIVRCompositor_GetTrackingSpace, ETrackingUniverseOrigin>();
}
EVRCompositorError PVRCompositor::WaitGetPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
    VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) {
  // getOut() << "wait get poses client 1" << std::endl;
  auto result = fnp.call<
    kIVRCompositor_WaitGetPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >(unRenderPoseArrayCount, unGamePoseArrayCount);
  // getOut() << "proxy wait get poses 1 " << (void *)pRenderPoseArray << " " << unRenderPoseArrayCount << " " << (void *)pGamePoseArray << " " << unGamePoseArrayCount << std::endl;
  memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(TrackedDevicePose_t));
  // getOut() << "proxy wait get poses 2 " << (void *)pRenderPoseArray << " " << unRenderPoseArrayCount << " " << (void *)pGamePoseArray << " " << unGamePoseArrayCount << std::endl;
  memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size() * sizeof(TrackedDevicePose_t));
  // getOut() << "proxy wait get poses 3 " << (void *)pRenderPoseArray << " " << unRenderPoseArrayCount << " " << (void *)pGamePoseArray << " " << unGamePoseArrayCount << std::endl;
  return std::get<0>(result);
}
EVRCompositorError PVRCompositor::GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
    VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) {
  // auto start = std::chrono::high_resolution_clock::now();
  auto result = fnp.call<
    kIVRCompositor_GetLastPoses,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    uint32_t,
    uint32_t
  >(unRenderPoseArrayCount, unGamePoseArrayCount);
  /* auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  getOut() << "get last poses call " << elapsed.count() << std::endl;  */
  memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(TrackedDevicePose_t));
  memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size() * sizeof(TrackedDevicePose_t));
  return std::get<0>(result);
}
EVRCompositorError PVRCompositor::GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) {
  auto result = fnp.call<
    kIVRCompositor_GetLastPoseForTrackedDeviceIndex,
    std::tuple<EVRCompositorError, managed_binary<TrackedDevicePose_t>, managed_binary<TrackedDevicePose_t>>,
    TrackedDeviceIndex_t
  >(unDeviceIndex);
  *pOutputPose = *std::get<1>(result).data();
  *pOutputGamePose = *std::get<2>(result).data();
  return std::get<0>(result);
}
void PVRCompositor::PrepareSubmit(const Texture_t *pTexture) {
  // getOut() << "prepare submit client 1" << std::endl;

  HRESULT hr;
  if (!device) {
    if (pTexture->eType == ETextureType::TextureType_DirectX) {
      // getOut() << "prepare submit client 2.1" << std::endl;
      ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);
      
      // getOut() << "initial tex 1" << std::endl;
      
      Microsoft::WRL::ComPtr<ID3D11Device> deviceBasic;
      tex->GetDevice(&deviceBasic);
      
      // getOut() << "initial tex 2" << std::endl;
      
      hr = deviceBasic->QueryInterface(__uuidof(ID3D11Device5), (void **)&device);
      // getOut() << "initial tex 3 " << (void *)device.Get() << std::endl;
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "device query failed" << std::endl;
        abort();
      }
      // getOut() << "initial tex 4" << std::endl;
      // ID3D11Texture2D1 *tex2;
      // hr = tex->QueryInterface(__uuidof(ID3D11Texture2D1), (void **)&tex2);
      
      // tex2->GetDevice(&device);
      // getOut() << "prepare submit client 2" << std::endl;
      // getOut() << "initial tex 5" << std::endl;
      // Microsoft::WRL::ComPtr<ID3D11DeviceContext1> contextBasic;
      // getOut() << "initial tex 6 " << (void *)device.Get() << std::endl;

      Microsoft::WRL::ComPtr<ID3D11DeviceContext3> context3;
      device->GetImmediateContext3(&context3);
      hr = context3->QueryInterface(__uuidof(ID3D11DeviceContext4), (void **)&context);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "context query failed" << std::endl;
        abort();
      }
      
      // getOut() << "initial tex 7 " << (void *)context.Get() << std::endl;
    } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
      {
        glewExperimental = true;
        auto result2 = glewInit();
        getOut() << "get p " << (void *)wglDXOpenDeviceNV << std::endl;
        if (result2 == GLEW_OK) {
          // nothing
        } else {
          const GLubyte *errorString = glewGetErrorString(result2);
          getOut() << "failed to initialize glew: " << (void *)result2 << " " << errorString << std::endl;
          // abort();
        }
      }
      {
        // getOut() << "init program 1" << std::endl;
        
        GLint oldProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
        GLint oldVao;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVao);
        GLint oldArrayBuffer;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &oldArrayBuffer);
        
        // getOut() << "init program 2.0 " << glGetString(GL_VERSION) << std::endl;

        glGenVertexArrays(1, &blitVao);
        // getOut() << "init program 2.1 " << blitVao << std::endl;
        glBindVertexArray(blitVao);
        
        // getOut() << "init program 3" << std::endl;

        // vertex shader
        GLuint composeVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(composeVertex, 1, &composeVsh, NULL);
        glCompileShader(composeVertex);
        GLint success;
        glGetShaderiv(composeVertex, GL_COMPILE_STATUS, &success);
        if (!success) {
          char infoLog[4096];
          GLsizei length;
          glGetShaderInfoLog(composeVertex, sizeof(infoLog), &length, infoLog);
          infoLog[length] = '\0';
          getOut() << "compose vertex shader compilation failed:\n" << infoLog << std::endl;
          abort();
        };

        // getOut() << "init program 4" << std::endl;

        // fragment shader
        GLuint composeFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(composeFragment, 1, &blitFsh, NULL);
        glCompileShader(composeFragment);
        glGetShaderiv(composeFragment, GL_COMPILE_STATUS, &success);
        if (!success) {
          char infoLog[4096];
          GLsizei length;
          glGetShaderInfoLog(composeFragment, sizeof(infoLog), &length, infoLog);
          infoLog[length] = '\0';
          getOut() << "compose fragment shader compilation failed:\n" << infoLog << std::endl;
          abort();
        };
        
        // getOut() << "init program 5" << std::endl;

        // shader program
        blitProgram = glCreateProgram();
        glAttachShader(blitProgram, composeVertex);
        glAttachShader(blitProgram, composeFragment);
        glLinkProgram(blitProgram);
        glGetProgramiv(blitProgram, GL_LINK_STATUS, &success);
        if (!success) {
          char infoLog[4096];
          GLsizei length;
          glGetShaderInfoLog(blitProgram, sizeof(infoLog), &length, infoLog);
          infoLog[length] = '\0';
          getOut() << "blit program linking failed\n" << infoLog << std::endl;
          abort();
        }
        
        // getOut() << "init program 6" << std::endl;

        GLuint positionLocation = glGetAttribLocation(blitProgram, "position");
        if (positionLocation == -1) {
          getOut() << "blit program failed to get attrib location for 'position'" << std::endl;
          abort();
        }
        // getOut() << "prepare submit server 13" << std::endl;
        GLuint uvLocation = glGetAttribLocation(blitProgram, "uv");
        if (uvLocation == -1) {
          getOut() << "blit program failed to get attrib location for 'uv'" << std::endl;
          abort();
        }

        // getOut() << "init program 6" << std::endl;

        std::string texString = std::string("tex");
        GLuint texLocation = glGetUniformLocation(blitProgram, texString.c_str());
        // getOut() << "get location 1  " << texString << " " << texLocation << std::endl;
        if (texLocation != -1) {
          // 
        } else {
          getOut() << "blit program failed to get uniform location for '" << texString << "'" << std::endl;
          abort();
        }
        
        // getOut() << "init program 7" << std::endl;

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(composeVertex);
        glDeleteShader(composeFragment);

        glUseProgram(blitProgram);

        GLuint positionBuffer;
        glGenBuffers(1, &positionBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
        static const float positions[] = {
          -1.0f, 1.0f,
          1.0f, 1.0f,
          -1.0f, -1.0f,
          1.0f, -1.0f,
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glEnableVertexAttribArray(positionLocation);
        glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, 0);

        // getOut() << "init program 8" << std::endl;

        GLuint uvBuffer;
        glGenBuffers(1, &uvBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        static const float uvs[] = {
          0.0f, 0.0f,
          1.0f, 0.0f,
          0.0f, 1.0f,
          1.0f, 1.0f,
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
        glEnableVertexAttribArray(uvLocation);
        glVertexAttribPointer(uvLocation, 2, GL_FLOAT, false, 0, 0);

        // getOut() << "init program 9" << std::endl;

        GLuint indexBuffer;
        glGenBuffers(1, &indexBuffer);
        static const uint16_t indices[] = {0, 2, 1, 2, 3, 1};
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glUniform1i(texLocation, 0);

        glBindVertexArray(oldVao);
        glUseProgram(oldProgram);
        glBindBuffer(GL_ARRAY_BUFFER, oldArrayBuffer);
      }

      // getOut() << "init program 10" << std::endl;

      int32_t adapterIndex;
      g_pvrsystem->GetDXGIOutputInfo(&adapterIndex);
      if (adapterIndex == -1) {
        adapterIndex = 0;
      }
      
      // getOut() << "init program 11" << std::endl;

      Microsoft::WRL::ComPtr<IDXGIFactory1> dxgi_factory;
      IDXGIAdapter *adapter;
      hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), &dxgi_factory);
      dxgi_factory->EnumAdapters(adapterIndex, &adapter);

      // getOut() << "init program 12" << std::endl;

      // Microsoft::WRL::ComPtr<ID3D11Device> device;
      // Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
      Microsoft::WRL::ComPtr<ID3D11Device> deviceBasic;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext> contextBasic;
      D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1
      };
      hr = D3D11CreateDevice(
        // adapter, // pAdapter
        NULL, // pAdapter
        D3D_DRIVER_TYPE_HARDWARE, // DriverType
        NULL, // Software
        0, // Flags
        featureLevels, // pFeatureLevels
        ARRAYSIZE(featureLevels), // FeatureLevels
        D3D11_SDK_VERSION, // SDKVersion
        &deviceBasic, // ppDevice
        NULL, // pFeatureLevel
        &contextBasic // ppImmediateContext
      );
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "opengl texture dx device creation failed " << (void *)hr << std::endl;
        abort();
      }
      
      // getOut() << "init program 13" << std::endl;
      
      hr = deviceBasic->QueryInterface(__uuidof(ID3D11Device5), (void **)&device);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "device query failed" << std::endl;
        abort();
      }
      
      // getOut() << "init program 14" << std::endl;

      Microsoft::WRL::ComPtr<ID3D11DeviceContext3> context3;
      device->GetImmediateContext3(&context3);
      hr = context3->QueryInterface(__uuidof(ID3D11DeviceContext4), (void **)&context);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "context query failed" << std::endl;
        abort();
      }

      /* {
        HMODULE module = LoadLibraryA("glew32.dll");
        wglDXOpenDeviceNV = reinterpret_cast<decltype(wglDXOpenDeviceNV)>(GetProcAddress(module, "__wglewDXOpenDeviceNV"));
        getOut() << "get p " << (void *)wglDXOpenDeviceNV << std::endl;
      } */

      // getOut() << "prepare submit client 2.7 " << (void *)wglDXOpenDeviceNV << " " << (void *)device.Get() << std::endl;

      hInteropDevice = wglDXOpenDeviceNV(device.Get());

      // getOut() << "prepare submit client 2.8" << std::endl;

      /* hr = contextBasic->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&context);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "context query failed" << std::endl;
        abort();
      } */

      /* scd.BufferCount = 1;                                    // one back buffer
      scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
      scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
      scd.OutputWindow = hWnd;                                // the window to be used
      scd.SampleDesc.Count = 4;                               // how many multisamples
      scd.Windowed = TRUE;                                    // windowed/full-screen mode

      HRESULT D3D11CreateDeviceAndSwapChain(
        &adapter, // pAdapter
        D3D_DRIVER_TYPE_HARDWARE, // DriverType
        NULL, // Software
        0, // Flags
        NULL, // pFeatureLevels
        0, // FeatureLevels
        D3D11_SDK_VERSION, // SDKVersion
        0, // pSwapChainDesc
        IDXGISwapChain             **ppSwapChain,
        ID3D11Device               **ppDevice,
        D3D_FEATURE_LEVEL          *pFeatureLevel,
        ID3D11DeviceContext        **ppImmediateContext
      ); */
    } else {
      getOut() << "unknown texture type: " << (void *)pTexture->eType << std::endl;
      abort();
    }
  }

  // getOut() << "prepare submit client 3" << std::endl;

  if (!fence) {
    hr = device->CreateFence(
      0, // value
      // D3D11_FENCE_FLAG_SHARED|D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER, // flags
      // D3D11_FENCE_FLAG_SHARED, // flags
      D3D11_FENCE_FLAG_NONE, // flags
      __uuidof(ID3D11Fence), // interface
      (void **)&fence // out
    );
    if (SUCCEEDED(hr)) {
      // getOut() << "created fence " << (void *)fence << std::endl;
      // nothing
    } else {
      getOut() << "failed to create fence" << std::endl;
      abort();
    }

    /* hr = fence->CreateSharedHandle(
      NULL, // security attributes
      GENERIC_ALL, // access
      L"Local\\OpenVrProxyFence", // name
      &fenceHandle // share handle
    );
    if (SUCCEEDED(hr)) {
      getOut() << "create shared fence handle " << (void *)fenceHandle << std::endl;
      // nothing
    } else {
      getOut() << "failed to create fence share handle" << std::endl;
      abort();
    } */
    
    // context->Flush();
  }

  /*HANDLE newFenceHandle = */fnp.call<
    kIVRCompositor_PrepareSubmit,
    int,
    ETextureType
  >(pTexture->eType);
  /* if (newFenceHandle != fenceHandle) {
    getOut() << "new fence check 1 " << (void *)newFenceHandle << std::endl;

    // IDisplayDeviceInterop *interop;
    // device.As(&interop);

    hr = device->OpenSharedFence(newFenceHandle, __uuidof(ID3D11Fence), (void **)&fence);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "fence resource unpack failed 2 " << (void *)hr << std::endl;
      abort();
    }

    getOut() << "new fence check 2 " << (void *)newFenceHandle << std::endl;
    
    fenceHandle = newFenceHandle;
  } */
  // getOut() << "prepare submit client 4" << std::endl;
}
EVRCompositorError PVRCompositor::Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags ) {
  // getOut() << "submit client 1 " << pTexture->eType << " " << pTexture->eColorSpace << std::endl;

  /* if (pTexture->eType == ETextureType::TextureType_OpenGL) {
    GLuint tex = (GLuint)pTexture->handle;

    // glBindTexture(GL_TEXTURE_2D, tex);
    GLint width, height;
    glGetTextureLevelParameteriv(tex, 0, GL_TEXTURE_WIDTH, &width);
    glGetTextureLevelParameteriv(tex, 0, GL_TEXTURE_HEIGHT, &height);
    // glBindTexture(GL_TEXTURE_2D, 0);

    getOut() << "got width height top " << width << " " << height << std::endl;
  } */

  auto key = std::pair<size_t, EVREye>(fnp.processId, eEye);
  auto iter = inFrontIndices.find(key);
  size_t index;
  if (iter != inFrontIndices.end()) {
    index = iter->second;
  } else {
    index = inDxTexs.size();
    inFrontIndices[key] = index;
    // iter = inFrontIndices.find(key);

    inDxTexs.resize(index+1, NULL);
    inShDxShareHandles.resize(index+1, NULL);
    inTexLatches.resize(index+1, NULL);
    interopTexs.resize(index+1, NULL);
    inReadInteropHandles.resize(index+1, NULL);
    inReadEvents.resize(index+1, NULL);
  }
  
  // getOut() << "submit client 2" << std::endl;

  managed_binary<VRTextureBounds_t> bounds(1);
  // getOut() << "submit client 23 " << bounds.size() << " " << (void *)pBounds << std::endl;
  if (pBounds) {
    *bounds.data() = *pBounds;
  } else {
    *bounds.data() = VRTextureBounds_t{
      0.0f, 0.0f,
      1.0f, 1.0f
    };
  }
  
  float uMin = std::min(bounds.data()->uMin, bounds.data()->uMax);
  float uMax = std::max(bounds.data()->uMin, bounds.data()->uMax);
  float vMin = std::min(bounds.data()->vMin, bounds.data()->vMax);
  float vMax = std::max(bounds.data()->vMin, bounds.data()->vMax);

  ID3D11Texture2D *&shTex = inDxTexs[index]; // shared dx texture
  HANDLE &sharedHandle = inShDxShareHandles[index]; // dx interop handle
  HANDLE &readEvent = inReadEvents[index]; // fence event
  uintptr_t &textureLatched = inTexLatches[index]; // remembered attachemnt
  if (textureLatched != (uintptr_t)pTexture->handle) {
    if (textureLatched) {
      // XXX delete old resources
    }
    textureLatched = (uintptr_t)pTexture->handle;

    // compute rexture params
    D3D11_TEXTURE2D_DESC desc{};
    if (pTexture->eType == ETextureType::TextureType_DirectX) {
      ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);
      
      // getOut() << "submit client 3" << std::endl;

      // getOut() << "submit client 4" << std::endl;

      tex->GetDesc(&desc);
      // getOut() << "old tex width " << desc.Width << " " << desc.Height << " " << (bounds.data()->uMax - bounds.data()->uMin) << " " << (bounds.data()->vMax - bounds.data()->vMin) << std::endl;
      width = desc.Width;
      height = desc.Height;
      desc.Width *= uMax - uMin;
      desc.Height *= vMax- vMin;
    } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
      GLuint tex = (GLuint)pTexture->handle;

      // glBindTexture(GL_TEXTURE_2D, tex);
      // GLint width, height;
      glGetTextureLevelParameteriv(tex, 0, GL_TEXTURE_WIDTH, (GLint *)&width);
      glGetTextureLevelParameteriv(tex, 0, GL_TEXTURE_HEIGHT, (GLint *)&height);
      // glBindTexture(GL_TEXTURE_2D, 0);
      // getOut() << "got width frontend " << width << " " << height << std::endl;

      desc.Width = width * (uMax - uMin);
      desc.Height = height * (vMax - vMin);
      desc.ArraySize = 1;
      // desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      // desc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
      desc.SampleDesc.Count = 1;
      desc.Usage = D3D11_USAGE_DEFAULT;
      // desc.BindFlags = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
      // desc.BindFlags = 40; // D3D11_BIND_DEPTH_STENCIL
      desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // D3D11_BIND_DEPTH_STENCIL
      // desc.MiscFlags = 0; //D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

      // XXX need to add the interop handle
    } else {
      getOut() << "unknown texture type: " << (void *)pTexture->eType << std::endl;
      abort();
    }

    // getOut() << "succ 0.1 " << desc.Width << " " << (void *)desc.BindFlags << " " << (void *)desc.MiscFlags << std::endl;
    
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
    desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    getOut() << "get texture desc front " << (int)eEye << " " <<
      (void *)device.Get() << " " <<
      desc.Width << " " << desc.Height << " " <<
      desc.ArraySize << " " <<
      desc.Format << " " <<
      desc.SampleDesc.Count << " " <<
      desc.Usage << " " <<
      desc.BindFlags << " " <<
      desc.MiscFlags << " " <<
      // pBounds->uMin << " " << pBounds->vMin << " " <<
      // pBounds->uMax << " " << pBounds->vMax << " " <<
      std::endl;

    // getOut() << "submit client 5" << std::endl;

    HRESULT hr = device->CreateTexture2D(
      &desc,
      NULL,
      &shTex
    );
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "failed to create shared texture: " << (void *)hr << std::endl;
      abort();
    }
    
    // getOut() << "get submit 6" << std::endl;

    // get gl interop for copying
    if (pTexture->eType == ETextureType::TextureType_OpenGL) {
      GLuint &interopTex = interopTexs[index];
      HANDLE &readInteropHandle = inReadInteropHandles[index];
      
      // getOut() << "get submit 7.1" << std::endl;
      // checkError("get submit 7.1");

      glGenTextures(1, &interopTex);
      // getOut() << "get submit 7.2 " << (void *)hInteropDevice << std::endl;
      // checkError("get submit 7.2");
      readInteropHandle = wglDXRegisterObjectNV(hInteropDevice, shTex, interopTex, GL_TEXTURE_2D, WGL_ACCESS_WRITE_DISCARD_NV);
      // getOut() << "get submit 7.3 " << (void *)readInteropHandle << std::endl;
      // checkError("get submit 7.3");
    }

    // getOut() << "get submit 8" << std::endl;

    // get share handle
    IDXGIResource1 *shTexResource;
    hr = shTex->QueryInterface(__uuidof(IDXGIResource1), (void **)&shTexResource);
    // getOut() << "submit client 7" << std::endl;
    // IDXGIResource1 *pDXGIResource;
    // HRESULT hr = tex->QueryInterface(__uuidof(IDXGIResource1), (void **)&pDXGIResource);

    if (SUCCEEDED(hr)) {
      // getOut() << "submit client 8" << std::endl;
      // getOut() << "submit client 7" << std::endl;
      hr = shTexResource->GetSharedHandle(&sharedHandle);
      // hr = shTexResource->CreateSharedHandle(NULL, DXGI_SHARED_RESOURCE_READ | DXGI_SHARED_RESOURCE_WRITE, NULL, &sharedHandle);

      // getOut() << "submit client 9" << std::endl;

      // getOut() << "succ 2 " << (void *)hr << " " << (void *)sharedHandle << std::endl;
      if (SUCCEEDED(hr)) {
        // getOut() << "submit client 10" << std::endl;
        // shTexResource->Release();
        // getOut() << "submit client 11" << std::endl;
        // nothing
      } else {
        getOut() << "failed to get shared texture handle: " << (void *)hr << std::endl;
        abort();
      }
    } else {
      getOut() << "failed to get shared texture: " << (void *)hr << std::endl;
      abort();
    }
    
    getOut() << "open frontend event " << (std::string("Local\\OpenVrFenceEvent") + std::to_string(std::get<0>(key)) + std::string(":") + std::to_string((int)std::get<1>(key))) << std::endl;
    readEvent = CreateEventA(
      NULL,
      false,
      false,
      (std::string("Local\\OpenVrFenceEvent") + std::to_string(std::get<0>(key)) + std::string(":") + std::to_string((int)std::get<1>(key))).c_str()
    );

    // getOut() << "submit client 13" << std::endl;
    
    if (!readEvent) {
      getOut() << "failed to open frontend event" << std::endl;
      abort();
    }
    
    // getOut() << "submit client 14" << std::endl;
  }
  
  // getOut() << "submit client 10" << std::endl;

  // getOut() << "submit client 11" << std::endl;

  /* uint32_t width = 1552;
  uint32_t height = 1552;
  D3D11_BOX srcBox;
  srcBox.left = pBounds->uMin * width;
  srcBox.right = pBounds->uMax * height;
  srcBox.top = pBounds->vMax * width;
  srcBox.bottom = pBounds->vMin * height;
  srcBox.front = 0;
  srcBox.back = 1;
  context->CopySubresourceRegion(shTex, 0, pBounds->uMin, pBounds->vMax, 0, tex, 0, &srcBox); */
  if (pTexture->eType == ETextureType::TextureType_DirectX) {
    // getOut() << "submit client 12" << std::endl;
    ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);
    // context->CopyResource(shTex, tex);
    D3D11_BOX srcBox{
      width * uMin,
      height * vMin,
      0,
      width * uMax,
      height * vMax,
      1
    };
    /* getOut() << "box " <<
      width * uMin << " " <<
      height * vMin << " " <<
      0 << " " <<
      width * uMax << " " <<
      height * vMax << " " <<
      1 << std::endl; */
    /* ID3D11Resource *shTex1 = nullptr;
    HRESULT hr = shTex->QueryInterface(__uuidof(ID3D11Resource), (void **)&shTex1);
    if (SUCCEEDED(hr)) {
    } else {
      getOut() << "copy fail 1" << std::endl;
    }
    ID3D11Resource *tex1 = nullptr;
    hr = tex->QueryInterface(__uuidof(ID3D11Resource), (void **)&tex1);
    if (SUCCEEDED(hr)) {
    } else {
      getOut() << "copy fail 2" << std::endl;
    } */
    context->CopySubresourceRegion(
      shTex,
      0,
      0,
      0,
      0,
      tex,
      0,
      &srcBox
    );
    // getOut() << "submit client 13" << std::endl;
    // context->Flush();
  } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
    // getOut() << "submit client 11" << std::endl;

    GLuint readTex = (GLuint)pTexture->handle;
    GLuint &interopTex = interopTexs[index];
    HANDLE &readInteropHandle = inReadInteropHandles[index];

    // getOut() << "submit client 12 " << (void *)readInteropHandle << std::endl;
    
    // checkError("submit client 12");

    HANDLE objects[] = {
      readInteropHandle
    };
    bool lockOk = wglDXLockObjectsNV(hInteropDevice, ARRAYSIZE(objects), objects);
    // getOut() << "submit client 13" << std::endl;
    // checkError("submit client 13");
    if (lockOk) {
      GLint oldActiveTexture;
      glGetIntegerv(GL_ACTIVE_TEXTURE, &oldActiveTexture);
      glActiveTexture(GL_TEXTURE0);
      GLint oldTexture2d;
      glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexture2d);
      glBindTexture(GL_TEXTURE_2D, readTex);

      GLint oldProgram;
      glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
      GLint oldVao;
      glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVao);
      GLint oldViewport[4];
      glGetIntegerv(GL_VIEWPORT, oldViewport);

      GLint oldReadFbo;
      glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &oldReadFbo);
      GLint oldDrawFbo;
      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &oldDrawFbo);

      // GLint width, height, internalFormat;
      // glGetTextureLevelParameteriv(readTex, 0, GL_TEXTURE_WIDTH, &width);
      // glGetTextureLevelParameteriv(readTex, 0, GL_TEXTURE_HEIGHT, &height);
      // glGetTextureLevelParameteriv(readTex, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);

      // getOut() << "got width height 3 " << (int)eEye << " " << readTex << " " << (void *)pBounds << " " << interopTex << " " << width << " " << height << " " << internalFormat << std::endl;

      // checkError("submit client 14");

      GLuint rwFbos[2];
      glGenFramebuffers(2, rwFbos);
      // GLuint &readFbo = rwFbos[0];
      // glBindFramebuffer(GL_READ_FRAMEBUFFER, readFbo);
      // glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, readTex, 0);
      GLuint &drawFbo = rwFbos[1];
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFbo);
      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, interopTex, 0);

      // checkError("submit client 16");

      // glBindTexture(GL_TEXTURE_2D, interopTex);

      // checkError("submit client 17");

      /* std::vector<unsigned char> data(4);
      glReadPixels(
        width/2,
        height/2,
        1,
        1,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data.data());

      checkError("submit client 17.1");

      getOut() << "got data " <<
        (int)data[0] << " " <<
        (int)data[1] << " " <<
        (int)data[2] << " " <<
        (int)data[3] << " " <<
        std::endl; */

      /* glCopyTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        0,
        0,
        width,
        height,
        0
      ); */
      // glClearColor(0.0, 0.0, 0.5, 1.0);
      // glClear(GL_COLOR_BUFFER_BIT);
      glBindVertexArray(blitVao);
      glUseProgram(blitProgram);
      
      // checkError("check error 1");
      
      glViewport(0, 0, width, height);
      glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_SHORT,
        (void *)0
      );

      // checkError("check error 2");

      /* glBlitFramebuffer(
        0,
        0,
        width/2,
        height/2,
        0,
        0,
        width/2,
        height/2,
        GL_COLOR_BUFFER_BIT,
        GL_LINEAR
      );
      // glFinish(); */

      // checkError("submit client 18");

      glBindVertexArray(oldVao);
      glUseProgram(oldProgram);
      glBindTexture(GL_TEXTURE_2D, oldTexture2d);
      glActiveTexture(oldActiveTexture);
      // glBindFramebuffer(GL_READ_FRAMEBUFFER, oldReadFbo);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, oldDrawFbo);
      glViewport(oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3]);
      // glReadBuffer(oldReadBuffer);
      glDeleteFramebuffers(ARRAYSIZE(rwFbos), rwFbos);

      // getOut() << "submit client 15" << std::endl;
      // checkError("submit client 19");
      bool unlockOk = wglDXUnlockObjectsNV(hInteropDevice, ARRAYSIZE(objects), objects);
      if (unlockOk) {
        // getOut() << "submit client 16" << std::endl;
        // checkError("submit client 20");
        // nothing
      } else {
        getOut() << "texture unlocking failed" << std::endl;
        abort();
      }
    } else {
      getOut() << "texture locking failed" << std::endl;
      abort();
    }
    // getOut() << "submit client 17" << std::endl;
  } else {
    getOut() << "unknown texture type: " << (void *)pTexture->eType << std::endl;
    abort();
  }

  // getOut() << "submit client 18 " << (void *)context.Get() << " " << (void *)fence.Get() << " " << (void *)readEvent << std::endl;

  ++fenceValue;
  getOut() << "signal read event " << (std::to_string(std::get<0>(key)) + std::string(":") + std::to_string((int)std::get<1>(key))) << " " << fenceValue << std::endl;
  context->Signal(fence.Get(), fenceValue);
  fence->SetEventOnCompletion(fenceValue, readEvent);
  // context->Flush();

  // getOut() << "submit client 19 " << (void *)sharedHandle << " " << (void *)pTexture << std::endl;

  // checkError("submit client 21");

  managed_binary<Texture_t> sharedTexture(1);
  *sharedTexture.data() = Texture_t{
    (void *)sharedHandle,
    // pTexture->eType,
    ETextureType::TextureType_DirectX,
    EColorSpace::ColorSpace_Auto,
    // pTexture->eColorSpace
  };
  const bool flip = bounds.data()->vMax < bounds.data()->vMin;
  *bounds.data() = VRTextureBounds_t{
    0.0f, flip ? 1.0f : 0.0f,
    1.0f, flip ? 0.0f : 1.0f
  };

  auto result = fnp.call<
    kIVRCompositor_Submit,
    EVRCompositorError,
    EVREye,
    managed_binary<Texture_t>,
    managed_binary<VRTextureBounds_t>,
    EVRSubmitFlags
  >(eEye, std::move(sharedTexture), std::move(bounds), EVRSubmitFlags::Submit_Default);

  // getOut() << "submit client 23" << std::endl;

  return result;
}
void PVRCompositor::FlushSubmit() {
  // getOut() << "flush submit client 1" << std::endl;
  fnp.call<
    kIVRCompositor_FlushSubmit,
    int
  >();
  // getOut() << "flush submit client 2" << std::endl;
}
void PVRCompositor::ClearLastSubmittedFrame() {
  fnp.call<
    kIVRCompositor_ClearLastSubmittedFrame,
    int
  >();
}
void PVRCompositor::PostPresentHandoff() {
  // getOut() << "post present handoff client 1" << std::endl;
  fnp.call<
    kIVRCompositor_PostPresentHandoff,
    int
  >();
  // getOut() << "post present handoff client 2" << std::endl;
}
bool PVRCompositor::GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo ) {
  /* managed_binary<Compositor_FrameTiming> timing(1);
  *timing.data() = *pTiming; */
  getOut() << "get frame timing 1" << std::endl;
  auto result = fnp.call<
    kIVRCompositor_GetFrameTiming,
    std::tuple<bool, managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >(unFramesAgo);
  getOut() << "get frame timing 2 " << (void *)pTiming << std::endl;
  *pTiming = *std::get<1>(result).data();
  getOut() << "get frame timing 3" << std::endl;
  return std::get<0>(result);
}
uint32_t PVRCompositor::GetFrameTimings( VR_ARRAY_COUNT( nFrames ) Compositor_FrameTiming *pTiming, uint32_t nFrames ) {
  /* managed_binary<Compositor_FrameTiming> timings(nFrames);
  memcpy(timings.data(), (void *)pTiming, nFrames * sizeof(Compositor_FrameTiming)); */
  auto result = fnp.call<
    kIVRCompositor_GetFrameTimings,
    std::tuple<uint32_t, managed_binary<Compositor_FrameTiming>>,
    uint32_t
  >(nFrames);
  memcpy((void *)pTiming, (void *)std::get<1>(result).data(), std::get<1>(result).size() * sizeof(Compositor_FrameTiming));
  return std::get<0>(result);
}
float PVRCompositor::GetFrameTimeRemaining() {
  return fnp.call<
    kIVRCompositor_GetFrameTimeRemaining,
    float
  >();
}
void PVRCompositor::GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) {
  auto result = fnp.call<
    kIVRCompositor_GetCumulativeStats,
    managed_binary<Compositor_CumulativeStats>,
    uint32_t
  >(nStatsSizeInBytes);
  *pStats = *result.data();
}
void PVRCompositor::FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground ) {
  fnp.call<
    kIVRCompositor_FadeToColor,
    int,
    float,
    float,
    float,
    float,
    float,
    bool
  >(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground);
}
HmdColor_t PVRCompositor::GetCurrentFadeColor( bool bBackground ) {
  auto result = fnp.call<
    kIVRCompositor_GetCurrentFadeColor,
    managed_binary<HmdColor_t>,
    bool
  >(bBackground);
  return *result.data();
}
void PVRCompositor::FadeGrid( float fSeconds, bool bFadeIn ) {
  fnp.call<
    kIVRCompositor_FadeGrid,
    int,
    float,
    bool
  >(fSeconds, bFadeIn);
}
float PVRCompositor::GetCurrentGridAlpha() {
  return fnp.call<
    kIVRCompositor_GetCurrentGridAlpha,
    float
  >();
}
EVRCompositorError PVRCompositor::SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount ) {
  getOut() << "SetSkyboxOverride" << std::endl;
  abort();
  return VRCompositorError_None;
}
void PVRCompositor::ClearSkyboxOverride() {
  fnp.call<
    kIVRCompositor_ClearSkyboxOverride,
    int
  >();
}
void PVRCompositor::CompositorBringToFront() {
  fnp.call<
    kIVRCompositor_CompositorBringToFront,
    int
  >();
}
void PVRCompositor::CompositorGoToBack() {
  fnp.call<
    kIVRCompositor_CompositorGoToBack,
    int
  >();
}
void PVRCompositor::CompositorQuit() {
  fnp.call<
    kIVRCompositor_CompositorQuit,
    int
  >();
}
bool PVRCompositor::IsFullscreen() {
  return fnp.call<
    kIVRCompositor_IsFullscreen,
    bool
  >();
}
uint32_t PVRCompositor::GetCurrentSceneFocusProcess() {
  return fnp.call<
    kIVRCompositor_GetCurrentSceneFocusProcess,
    uint32_t
  >();
}
uint32_t PVRCompositor::GetLastFrameRenderer() {
  return fnp.call<
    kIVRCompositor_GetLastFrameRenderer,
    uint32_t
  >();
}
bool PVRCompositor::CanRenderScene() {
  return fnp.call<
    kIVRCompositor_CanRenderScene,
    bool
  >();
}
void PVRCompositor::ShowMirrorWindow() {
  fnp.call<
    kIVRCompositor_ShowMirrorWindow,
    int
  >();
}
void PVRCompositor::HideMirrorWindow() {
  fnp.call<
    kIVRCompositor_HideMirrorWindow,
    int
  >();
}
bool PVRCompositor::IsMirrorWindowVisible() {
  return fnp.call<
    kIVRCompositor_IsMirrorWindowVisible,
    int
  >();
}
void PVRCompositor::CompositorDumpImages() {
  fnp.call<
    kIVRCompositor_CompositorDumpImages,
    int
  >();
}
bool PVRCompositor::ShouldAppRenderWithLowResources() {
  return fnp.call<
    kIVRCompositor_ShouldAppRenderWithLowResources,
    bool
  >();
}
void PVRCompositor::ForceInterleavedReprojectionOn( bool bOverride ) {
  fnp.call<
    kIVRCompositor_ShouldAppRenderWithLowResources,
    int,
    bool
  >(bOverride);
}
void PVRCompositor::ForceReconnectProcess() {
  fnp.call<
    kIVRCompositor_ForceReconnectProcess,
    int
  >();
}
void PVRCompositor::SuspendRendering( bool bSuspend ) {
  fnp.call<
    kIVRCompositor_SuspendRendering,
    int,
    bool
  >(bSuspend);
}
vr::EVRCompositorError PVRCompositor::GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) {
  abort();
  return VRCompositorError_None;
}
void PVRCompositor::ReleaseMirrorTextureD3D11( void *pD3D11ShaderResourceView ) {
  abort();
}
vr::EVRCompositorError PVRCompositor::GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) {
  abort();
  return VRCompositorError_None;
}
bool PVRCompositor::ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) {
  abort();
  return false;
}
void PVRCompositor::LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) {
  abort();
}
void PVRCompositor::UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) {
  abort();
}
uint32_t PVRCompositor::GetVulkanInstanceExtensionsRequired( VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) {
  abort();
  return 0;
}
uint32_t PVRCompositor::GetVulkanDeviceExtensionsRequired( VkPhysicalDevice_T *pPhysicalDevice, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize ) {
  abort();
  return 0;
}
void PVRCompositor::SetExplicitTimingMode( EVRCompositorTimingMode eTimingMode ) {
  fnp.call<
    kIVRCompositor_SetExplicitTimingMode,
    int,
    EVRCompositorTimingMode
  >(eTimingMode);
}
EVRCompositorError PVRCompositor::SubmitExplicitTimingData() {
  return fnp.call<
    kIVRCompositor_SubmitExplicitTimingData,
    EVRCompositorError
  >();
}
bool PVRCompositor::IsMotionSmoothingEnabled() {
  return fnp.call<
    kIVRCompositor_IsMotionSmoothingEnabled,
    bool
  >();
}
bool PVRCompositor::IsMotionSmoothingSupported() {
  return fnp.call<
    kIVRCompositor_IsMotionSmoothingSupported,
    bool
  >();
}
bool PVRCompositor::IsCurrentSceneFocusAppLoading() {
  return fnp.call<
    kIVRCompositor_IsCurrentSceneFocusAppLoading,
    bool
  >();
}
void PVRCompositor::CacheWaitGetPoses() {
  getOut() << "CacheWaitGetPoses 1" << std::endl;
  EVRCompositorError error = vrcompositor->WaitGetPoses(cachedRenderPoses, ARRAYSIZE(cachedRenderPoses), cachedGamePoses, ARRAYSIZE(cachedGamePoses));
  getOut() << "CacheWaitGetPoses 2" << std::endl;
  if (error != VRCompositorError_None) {
    getOut() << "compositor WaitGetPoses error: " << (void *)error << std::endl;
  }
  inBackReadEventQueue.clear();
}
}