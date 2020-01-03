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
// uniform  sampler2D depthTex;\n\
\n\
void main() {\n\
  if (hasTex1 > 0.0) {\n\
    vec4 c = texture(tex1, vUv);\n\
    fragColor += vec4(c.rgb*c.a, c.a);\n\
  }\n\
  if (hasTex2 > 0.0) {\n\
    vec4 c = texture(tex2, vUv);\n\
    fragColor += vec4(c.rgb*c.a, c.a);\n\
  }\n\
  // if (fragColor.a < 0.5) discard;\n\
  // fragColor = vec4(vec3(0.0), 1.0);\n\
  // fragColor.r += 0.1;\n\
  // gl_FragDepth = texture(depthTex, vUv).r;\n\
}\n\
";
constexpr size_t MAX_LAYERS = 2;
const EVREye EYES[] = {
  Eye_Left,
  Eye_Right,
};

PVRCompositor::PVRCompositor(IVRSystem *vrsystem, IVRCompositor *vrcompositor, FnProxy &fnp) : vrcompositor(vrcompositor), fnp(fnp) {
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

    EVRCompositorError error = vrcompositor->WaitGetPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);

    // getOut() << "handle poses 3" << std::endl;

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

    // auto start = std::chrono::high_resolution_clock::now();
    EVRCompositorError error = vrcompositor->GetLastPoses(renderPoseArray.data(), unRenderPoseArrayCount, gamePoseArray.data(), unGamePoseArrayCount);
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
    HANDLE,
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
      
      getOut() << "creating device 1" << std::endl;

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
      getOut() << "creating device 2" << std::endl;
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

      if (!fence) {
        hr = device->CreateFence(
          0, // value
          D3D11_FENCE_FLAG_SHARED, // flags
          __uuidof(ID3D11Fence), // interface
          (void **)&fence // out
        );
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to create fence" << std::endl;
          abort();
        }

        hr = fence->CreateSharedHandle(
          NULL, // security attributes
          GENERIC_ALL, // access
          L"Local\\OpenVrProxyFence", // name
          &fenceHandle // share handle
        );
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to create fence share handle" << std::endl;
          abort();
        }
      }

      subWindow = initGl();

      // getOut() << "prepare submit server 4 " << (void *)device.Get() << std::endl;

      // getOut() << "gl init 1 " << (void *)subWindow << " " << (void *)device.Get() << " " << glGetError() << std::endl;

      getOut() << "open interop device 1 " << (void *)device.Get() << std::endl;

      hInteropDevice = wglDXOpenDeviceNV(device.Get());
      
      getOut() << "open interop device 2 " << (void *)hInteropDevice << std::endl;

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
      
      getOut() << "getting width height" << std::endl;
      
      // getOut() << "prepare submit server 7" << std::endl;

      // getOut() << "gl init 4 " << glGetError() << std::endl;

      // glBindTexture(GL_TEXTURE_2D, shTexOutId);
      // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      g_vrsystem->GetRecommendedRenderTargetSize(&width, &height);
      getOut() << "got width height " << width << " " << height << std::endl;
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
      getOut() << "interop 1" << std::endl;
      for (int i = 0; i < 2; i++) {
        HRESULT hr = device->CreateTexture2D(
          &desc,
          NULL,
          &shTexOuts[i]
        );
        shTexOutInteropHandles[i] = wglDXRegisterObjectNV(hInteropDevice, shTexOuts[i], shTexOutIds[i], GL_TEXTURE_2D, WGL_ACCESS_WRITE_DISCARD_NV);
      }
      getOut() << "interop 2" << std::endl;
      
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
      
      // getOut() << "prepare submit server 10" << std::endl;

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
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
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
    
    getOut() << "interop 3 " << (void *)fenceHandle << std::endl;
    
    // getOut() << "prepare submit server 20" << std::endl;

    return fenceHandle;
  });
  fnp.reg<
    kIVRCompositor_Submit,
    EVRCompositorError,
    EVREye,
    managed_binary<Texture_t>,
    managed_binary<VRTextureBounds_t>,
    EVRSubmitFlags
  >([=](EVREye eEye, managed_binary<Texture_t> sharedTexture, managed_binary<VRTextureBounds_t> bounds, EVRSubmitFlags submitFlags) {
    Texture_t *pTexture = sharedTexture.data();
    VRTextureBounds_t *pBounds = bounds.data();
    
    getOut() << "submit server 1" << std::endl;

    auto key = std::pair<size_t, EVREye>(fnp.remoteCallbackId, eEye);
    auto iter = inBackIndices.find(key);
    size_t index;
    if (iter != inBackIndices.end()) {
      index = iter->second;
    } else {
      index = inBackTexs.size();
      inBackIndices[key] = index;
      // iter = inBackIndices.find(key);

      inBackTexs.resize(index+1, NULL);
      inBackInteropHandles.resize(index+1, NULL);
      inBackHandleLatches.resize(index+1, NULL);
    }
    
    getOut() << "submit server 2" << std::endl;

    HANDLE sharedHandle = (HANDLE)pTexture->handle;
    GLuint &shTexInId = inBackTexs[index]; // gl texture
    HANDLE &shTexInInteropHandle = inBackInteropHandles[index]; // interop texture handle
    HANDLE &handleLatched = inBackHandleLatches[index]; // remembered attachemnt

    getOut() << "submit server 3" << std::endl;

    if (handleLatched != sharedHandle) {
      // getOut() << "got shTex in " << (void *)sharedHandle << std::endl;
      if (handleLatched) {
        // glDeleteTextures(1, &shTexInId);
        // XXX delete old resources
        // hr = device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&pD3DResource));
      }
      handleLatched = sharedHandle;

      getOut() << "submit server 4" << std::endl;

      // IDXGIResource1 *pD3DResource;
      // HRESULT hr = device->OpenSharedResource1(sharedHandle, __uuidof(IDXGIResource1), (void**)(&pD3DResource));
      ID3D11Resource *shTexResource;
      HRESULT hr = device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&shTexResource));

      getOut() << "submit server 5" << std::endl;

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
    
      getOut() << "submit server 6 " << GetLastError() << std::endl;

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

      getOut() << "submit server 7" << std::endl;
    }
    
    if (!fence) {
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
    }

    getOut() << "submit server 9" << std::endl;

    ++fenceValue;
    context->Wait(fence.Get(), fenceValue);
    
    getOut() << "submit server 9" << std::endl;

    return VRCompositorError_None;
  });
  fnp.reg<
    kIVRCompositor_FlushSubmit,
    int,
    EVREye
  >([=](EVREye eEye) {
    getOut() << "flush submit server 1" << std::endl;
    
    int iEye = (int)eEye;
      
    std::vector<HANDLE> objects;
    objects.reserve(inBackIndices.size()/2 + 1);
    for (auto iter : inBackIndices) {
      EVREye e = iter.first.second;
      if (e == eEye) {
        size_t index = iter.second;
        HANDLE h = inBackInteropHandles[index];
        objects.push_back(h);
        getOut() << "got handle " << (void *)h << std::endl;
      }
    }
    objects.push_back(shTexOutInteropHandles[iEye]);
    getOut() << "got handle end " << (void *)shTexOutInteropHandles[iEye] << std::endl;
    
    getOut() << "flush submit server 2 " << " " << (void *)hInteropDevice << std::endl;
    
    bool lockOk = wglDXLockObjectsNV(hInteropDevice, objects.size(), objects.data());
    getOut() << "gl init error 11 " << lockOk << " " << glGetError() << std::endl;
    if (lockOk) {
      // getOut() << "flush submit server 3 " << (int)eye << std::endl;

      size_t numLayers = 0;
      for (auto iter : inBackIndices) {
        EVREye e = iter.first.second;
        if (e == eEye) {
          size_t &index = iter.second;

          glActiveTexture(GL_TEXTURE0 + numLayers);
          glBindTexture(GL_TEXTURE_2D, inBackTexs[index]);
          glUniform1f(hasTexLocations[numLayers], 1.0f);

          numLayers++;
          if (numLayers >= MAX_LAYERS) {
            break;
          }
        }
      }
      // getOut() << "flush submit server 4 " << (int)eye << std::endl;
      for (size_t i = numLayers; i < MAX_LAYERS; i++) {
        // glActiveTexture(GL_TEXTURE0 + i);
        // glBindTexture(GL_TEXTURE_2D, 0);
        glUniform1f(hasTexLocations[i], 0.0f);
      }
      
      // getOut() << "flush submit server 5 " << (int)eye << std::endl;

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
      // getOut() << "gl init error 16 " << glGetError() << std::endl;

      // getOut() << "flush submit server 6 " << (int)eye << std::endl;

      // getOut() << "gl submit 1 " << glGetError() << std::endl;
      // pTexture->handle = (void *)shTexOut;
      // getOut() << "flush submit server 8" << std::endl;
      // getOut() << "flush submit server 9" << std::endl;
      bool unlockOk = wglDXUnlockObjectsNV(hInteropDevice, objects.size(), objects.data());
      // getOut() << "flush submit server 9 " << unlockOk << std::endl;
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
        getOut() << "gl submit 2 " << glGetError() << std::endl;
        vrcompositor->Submit(eEye, &texture, &bounds, EVRSubmitFlags::Submit_Default);
      } else {
        getOut() << "texture unlocking failed" << std::endl;
        abort();
      }
    } else {
      getOut() << "texture locking failed" << std::endl;
      abort();
    }
    // vrcompositor->PostPresentHandoff();
    
    getOut() << "flush submit server 11" << std::endl;
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
    vrcompositor->PostPresentHandoff();
    return 0;
  });
  fnp.reg<
    kIVRCompositor_GetFrameTiming,
    std::tuple<bool, managed_binary<Compositor_FrameTiming>>,
    managed_binary<Compositor_FrameTiming>,
    uint32_t
  >([=](managed_binary<Compositor_FrameTiming> timing, uint32_t unFramesAgo) {
    //  managed_binary<Compositor_FrameTiming> timing(1);

    bool result = vrcompositor->GetFrameTiming(timing.data(), unFramesAgo);

    return std::tuple<bool, managed_binary<Compositor_FrameTiming>>(
      result,
      std::move(timing)
    );
  });
  fnp.reg<
    kIVRCompositor_GetFrameTimings,
    std::tuple<uint32_t, managed_binary<Compositor_FrameTiming>>,
    managed_binary<Compositor_FrameTiming>,
    uint32_t
  >([=](managed_binary<Compositor_FrameTiming> timings, uint32_t nFrames) {
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
  // getOut() << "wait get poses 1 " << unRenderPoseArrayCount << " " << unGamePoseArrayCount << " " << std::get<1>(result).size() << " " << std::get<2>(result).size() << std::endl;
  memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(*std::get<1>(result).data()));
  // getOut() << "wait get poses 2 " << unRenderPoseArrayCount << " " << unGamePoseArrayCount << " " << std::get<1>(result).size() << " " << std::get<2>(result).size() << std::endl;
  memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size() * sizeof(*std::get<2>(result).data()));
  // getOut() << "wait get poses 3 " << unRenderPoseArrayCount << " " << unGamePoseArrayCount << " " << std::get<1>(result).size() << " " << std::get<2>(result).size() << std::endl;
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
  memcpy(pRenderPoseArray, std::get<1>(result).data(), std::get<1>(result).size() * sizeof(*std::get<1>(result).data()));
  memcpy(pGamePoseArray, std::get<2>(result).data(), std::get<2>(result).size() * sizeof(*std::get<2>(result).data()));
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
  if (pTexture->eType == ETextureType::TextureType_DirectX) {
    // getOut() << "prepare submit client 2.1" << std::endl;
    if (!device) {
      ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);
      
      getOut() << "initial tex 1" << std::endl;
      
      Microsoft::WRL::ComPtr<ID3D11Device> deviceBasic;
      tex->GetDevice(&deviceBasic);
      
      getOut() << "initial tex 2" << std::endl;
      
      hr = deviceBasic->QueryInterface(__uuidof(ID3D11Device5), (void **)&device);
      getOut() << "initial tex 3 " << (void *)device.Get() << std::endl;
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "device query failed" << std::endl;
        abort();
      }
      getOut() << "initial tex 4" << std::endl;
      // ID3D11Texture2D1 *tex2;
      // hr = tex->QueryInterface(__uuidof(ID3D11Texture2D1), (void **)&tex2);
      
      // tex2->GetDevice(&device);
    }
    // getOut() << "prepare submit client 2" << std::endl;
    if (!context) {
      getOut() << "initial tex 5" << std::endl;
      // Microsoft::WRL::ComPtr<ID3D11DeviceContext1> contextBasic;
      getOut() << "initial tex 6 " << (void *)device.Get() << std::endl;

      Microsoft::WRL::ComPtr<ID3D11DeviceContext3> context3;
      device->GetImmediateContext3(&context3);
      hr = context3->QueryInterface(__uuidof(ID3D11DeviceContext4), (void **)&context);
      if (SUCCEEDED(hr)) {
        // nothing
      } else {
        getOut() << "context query failed" << std::endl;
        abort();
      }
      
      getOut() << "initial tex 7 " << (void *)context.Get() << std::endl;
    }
  } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
    // getOut() << "prepare submit client 2.2" << std::endl;
    int32_t adapterIndex;
    g_vrsystem->GetDXGIOutputInfo(&adapterIndex);
    if (adapterIndex == -1) {
      adapterIndex = 0;
    }

    Microsoft::WRL::ComPtr<IDXGIFactory1> dxgi_factory;
    IDXGIAdapter *adapter;
    hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), &dxgi_factory);
    dxgi_factory->EnumAdapters(adapterIndex, &adapter);

    // Microsoft::WRL::ComPtr<ID3D11Device> device;
    // Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
    Microsoft::WRL::ComPtr<ID3D11Device> deviceBasic;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> contextBasic;
    D3D11CreateDevice(
      adapter, // pAdapter
      D3D_DRIVER_TYPE_HARDWARE, // DriverType
      NULL, // Software
      0, // Flags
      NULL, // pFeatureLevels
      0, // FeatureLevels
      D3D11_SDK_VERSION, // SDKVersion
      &deviceBasic, // ppDevice
      NULL, // pFeatureLevel
      &contextBasic // ppImmediateContext
    );
    
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
  
  // getOut() << "prepare submit client 3" << std::endl;

  HANDLE newFenceHandle = fnp.call<
    kIVRCompositor_PrepareSubmit,
    HANDLE,
    ETextureType
  >(pTexture->eType);
  if (newFenceHandle != fenceHandle) {
    getOut() << "new fence check 1 " << (void *)newFenceHandle << std::endl;

    hr = device->OpenSharedFence(newFenceHandle, __uuidof(ID3D11Fence), (void **)&fence);
    if (SUCCEEDED(hr)) {
      // nothing
    } else {
      getOut() << "fence resource unpack failed" << std::endl;
      abort();
    }

    getOut() << "new fence check 2 " << (void *)newFenceHandle << std::endl;
    
    fenceHandle = newFenceHandle;
  }
  // getOut() << "prepare submit client 4" << std::endl;
}
EVRCompositorError PVRCompositor::Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags ) {
  getOut() << "submit client 1" << std::endl;

  auto key = std::pair<size_t, EVREye>(fnp.callbackId, eEye);
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
  }
  
  // getOut() << "submit client 2" << std::endl;

  ID3D11Texture2D *&shTex = inDxTexs[index]; // shared dx texture
  HANDLE &sharedHandle = inShDxShareHandles[index]; // dx interop handle
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
    } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
      GLuint tex = (GLuint)pTexture->handle;

      glBindTexture(GL_TEXTURE_2D, tex);
      GLint width, height;
      glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WIDTH, &width);
      glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_HEIGHT, &height);
      glBindTexture(GL_TEXTURE_2D, 0);

      desc.Width = width;
      desc.Height = height;
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

    /* getOut() << "get texture desc front " << (int)eEye << " " <<
      (void *)tex << " " << desc.Width << " " << desc.Height << " " <<
      desc.ArraySize << " " <<
      desc.Format << " " <<
      desc.SampleDesc.Count << " " <<
      desc.Usage << " " <<
      desc.BindFlags << " " <<
      desc.MiscFlags << " " <<
      // pBounds->uMin << " " << pBounds->vMin << " " <<
      // pBounds->uMax << " " << pBounds->vMax << " " <<
      std::endl; */

    // getOut() << "succ 0.1 " << desc.Width << " " << (void *)desc.BindFlags << " " << (void *)desc.MiscFlags << std::endl;
    
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED_NTHANDLE | D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
    desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    getOut() << "submit client 5" << std::endl;

    HRESULT hr = device->CreateTexture2D(
      &desc,
      NULL,
      &shTex
    );

    if (SUCCEEDED(hr)) {
      getOut() << "get submit 6" << std::endl;
    } else {
      getOut() << "failed to create shared texture: " << (void *)hr << std::endl;
      abort();
    }

    // get gl interop for copying
    if (pTexture->eType == ETextureType::TextureType_OpenGL) {
      GLuint &interopTex = interopTexs[index];
      HANDLE &readInteropHandle = inReadInteropHandles[index];

      glGenTextures(1, &interopTex);
      readInteropHandle = wglDXRegisterObjectNV(hInteropDevice, shTex, interopTex, GL_TEXTURE_2D, WGL_ACCESS_WRITE_DISCARD_NV);
    }

    getOut() << "submit client 6" << std::endl;

    // get share handle
    IDXGIResource1 *shTexResource;
    hr = shTex->QueryInterface(__uuidof(IDXGIResource1), (void **)&shTexResource);
    getOut() << "submit client 7" << std::endl;
    // IDXGIResource1 *pDXGIResource;
    // HRESULT hr = tex->QueryInterface(__uuidof(IDXGIResource1), (void **)&pDXGIResource);

    if (SUCCEEDED(hr)) {
      getOut() << "submit client 8" << std::endl;
      // getOut() << "submit client 7" << std::endl;
      hr = shTexResource->GetSharedHandle(&sharedHandle);
      // hr = shTexResource->CreateSharedHandle(NULL, DXGI_SHARED_RESOURCE_READ | DXGI_SHARED_RESOURCE_WRITE, NULL, &sharedHandle);

      getOut() << "submit client 9" << std::endl;

      // getOut() << "succ 2 " << (void *)hr << " " << (void *)sharedHandle << std::endl;
      if (SUCCEEDED(hr)) {
        getOut() << "submit client 10" << std::endl;
        // shTexResource->Release();
        getOut() << "submit client 11" << std::endl;
        // nothing
      } else {
        getOut() << "failed to get shared texture handle: " << (void *)hr << std::endl;
        abort();
      }
    } else {
      getOut() << "failed to get shared texture: " << (void *)hr << std::endl;
      abort();
    }
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
    context->CopyResource(shTex, tex);
    // getOut() << "submit client 13" << std::endl;
    // context->Flush();
  } else if (pTexture->eType == ETextureType::TextureType_OpenGL) {
    GLuint readTex = (GLuint)pTexture->handle;
    GLuint &interopTex = interopTexs[index];
    HANDLE &readInteropHandle = inReadInteropHandles[index];

    HANDLE objects[] = {
      readInteropHandle
    };
    bool lockOk = wglDXLockObjectsNV(hInteropDevice, ARRAYSIZE(objects), objects);
    // getOut() << "gl init error 11 " << lockOk << " " << glGetError() << std::endl;
    if (lockOk) {
      GLint oldReadFbo;
      glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &oldReadFbo);
      GLint oldReadBuffer;
      glGetIntegerv(GL_READ_BUFFER, &oldReadBuffer);

      glBindTexture(GL_TEXTURE_2D, readTex);
      GLint width, height;
      glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WIDTH, &width);
      glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_HEIGHT, &height);

      GLuint readFbo;
      glGenFramebuffers(1, &readFbo);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, readFbo);
      glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, readTex, 0);
      glReadBuffer(GL_COLOR_ATTACHMENT0);

      glBindTexture(GL_TEXTURE_2D, interopTex);

      glCopyTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        0,
        0,
        width,
        height,
        0
      );

      glBindTexture(GL_TEXTURE_2D, 0);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, oldReadFbo);
      glReadBuffer(oldReadBuffer);
      glDeleteFramebuffers(1, &readFbo);

      bool unlockOk = wglDXUnlockObjectsNV(hInteropDevice, ARRAYSIZE(objects), objects);
      if (unlockOk) {
        // nothing
      } else {
        getOut() << "texture unlocking failed" << std::endl;
        abort();
      }
    } else {
      getOut() << "texture locking failed" << std::endl;
      abort();
    }
  } else {
    getOut() << "unknown texture type: " << (void *)pTexture->eType << std::endl;
    abort();
  }

  ++fenceValue;
  context->Signal(fence.Get(), fenceValue);

  getOut() << "submit client 14" << std::endl;
  
  managed_binary<Texture_t> sharedTexture(1);
  *sharedTexture.data() = Texture_t{
    (void *)sharedHandle,
    pTexture->eType,
    pTexture->eColorSpace
  };
  managed_binary<VRTextureBounds_t> bounds(1);
  *bounds.data() = *pBounds;

  getOut() << "submit client 15" << std::endl;

  return fnp.call<
    kIVRCompositor_Submit,
    EVRCompositorError,
    EVREye,
    managed_binary<Texture_t>,
    managed_binary<VRTextureBounds_t>,
    EVRSubmitFlags
  >(eEye, std::move(sharedTexture), std::move(bounds), nSubmitFlags);
}
void PVRCompositor::FlushSubmit(EVREye eEye) {
  fnp.call<
    kIVRCompositor_FlushSubmit,
    int,
    EVREye
  >(eEye);
}
void PVRCompositor::ClearLastSubmittedFrame() {
  fnp.call<
    kIVRCompositor_ClearLastSubmittedFrame,
    int
  >();
}
void PVRCompositor::PostPresentHandoff() {
  fnp.call<
    kIVRCompositor_PostPresentHandoff,
    int
  >();
}
bool PVRCompositor::GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo ) {
  managed_binary<Compositor_FrameTiming> timing(1);
  *timing.data() = *pTiming;
  auto result = fnp.call<
    kIVRCompositor_GetFrameTiming,
    std::tuple<bool, managed_binary<Compositor_FrameTiming>>,
    managed_binary<Compositor_FrameTiming>,
    uint32_t
  >(std::move(timing), unFramesAgo);
  *pTiming = *std::get<1>(result).data();
  return std::get<0>(result);
}
uint32_t PVRCompositor::GetFrameTimings( VR_ARRAY_COUNT( nFrames ) Compositor_FrameTiming *pTiming, uint32_t nFrames ) {
  managed_binary<Compositor_FrameTiming> timings(nFrames);
  memcpy(timings.data(), (void *)pTiming, nFrames * sizeof(Compositor_FrameTiming));
  auto result = fnp.call<
    kIVRCompositor_GetFrameTimings,
    std::tuple<uint32_t, managed_binary<Compositor_FrameTiming>>,
    managed_binary<Compositor_FrameTiming>,
    uint32_t
  >(std::move(timings), nFrames);
  memcpy((void *)pTiming, (void *)std::get<1>(result).data(), nFrames * sizeof(Compositor_FrameTiming));
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
}