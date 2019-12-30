// #include <chrono>
#include "device/vr/openvr/test/proxy.h"

namespace vr {
char kIVRCompositor_SetTrackingSpace[] = "IVRCompositor::SetTrackingSpace";
char kIVRCompositor_GetTrackingSpace[] = "IVRCompositor::GetTrackingSpace";
char kIVRCompositor_WaitGetPoses[] = "IVRCompositor::WaitGetPoses";
char kIVRCompositor_GetLastPoses[] = "IVRCompositor::GetLastPoses";
char kIVRCompositor_GetLastPoseForTrackedDeviceIndex[] = "IVRCompositor::GetLastPoseForTrackedDeviceIndex";
char kIVRCompositor_Submit[] = "IVRCompositor::Submit";
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
uniform sampler2D tex;\n\
// uniform  sampler2D depthTex;\n\
\n\
void main() {\n\
  fragColor = texture(tex, vUv);\n\
  // fragColor = vec4(vec3(0.0), 1.0);\n\
  // fragColor.r += 0.1;\n\
  // gl_FragDepth = texture(depthTex, vUv).r;\n\
}\n\
";

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
    // getOut() << "handle poses 1" << std::endl;
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
    kIVRCompositor_Submit,
    EVRCompositorError,
    EVREye,
    managed_binary<Texture_t>,
    managed_binary<VRTextureBounds_t>,
    EVRSubmitFlags,
    uintptr_t
  >([=](EVREye eEye, managed_binary<Texture_t> sharedTexture, managed_binary<VRTextureBounds_t> bounds, EVRSubmitFlags submitFlags, uintptr_t pDevice) {
    Texture_t *pTexture = sharedTexture.data();
    VRTextureBounds_t *pBounds = bounds.data();

    if (!device) {
      device = (ID3D11Device *)pDevice;
    }

    ID3D11Texture2D *&shTexIn = eEye == Eye_Left ? shTexLeft : shTexRight;
    ID3D11Texture2D *&shTexOut = eEye == Eye_Left ? shTexLeft2 : shTexRight2;
    GLuint &fbo = eEye == Eye_Left ? shFboLeft : shFboRight;
    GLuint &shTexInId = eEye == Eye_Left ? shTexInLeft : shTexInRight;
    HANDLE &shTexInObjectHandle = eEye == Eye_Left ? shTexInLeftObjectHandle : shTexInRightObjectHandle;
    HANDLE &shTexOutObjectHandle = eEye == Eye_Left ? shTexOutLeftObjectHandle : shTexOutRightObjectHandle;
    if (!shTexIn) {
      HANDLE sharedHandle = (HANDLE)pTexture->handle;
      getOut() << "got shTex in " << (void *)sharedHandle << std::endl;

      ID3D11Resource *pD3DResource;
      HRESULT hr = device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&pD3DResource));
      
      if (SUCCEEDED(hr)) {
        hr = pD3DResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&shTexIn));
        
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to unpack shared texture: " << (void *)hr << " " << (void *)sharedHandle << std::endl;
          abort();
        }

        pD3DResource->Release();
      } else {
        getOut() << "failed to unpack shared texture handle: " << (void *)hr << " " << (void *)sharedHandle << std::endl;
        abort();
      }
    // }
    // if (!shTexOut) {
      D3D11_TEXTURE2D_DESC desc;
      shTexIn->GetDesc(&desc);
      
      getOut() << "get texture desc 2 " << (int)eEye << " " << desc.Width << " " << desc.Height << " " << desc.Format << " " << desc.MiscFlags << std::endl;

      // getOut() << "succ 0.1 " << desc.Width << " " << (void *)desc.BindFlags << " " << (void *)desc.MiscFlags << std::endl;

      // desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

      hr = device->CreateTexture2D(
        &desc,
        NULL,
        &shTexOut
      );
    // }
      if (!subWindow) {
        subWindow = initGl();
      }

      // getOut() << "create shared 1" << std::endl;
      GLuint textures[3];
      glCreateTextures(GL_TEXTURE_2D, ARRAYSIZE(textures), textures);
      shTexInId = textures[0];
      GLuint shTexOutId = textures[1];
      GLuint texDepthId = textures[2];
      glBindTexture(GL_TEXTURE_2D, shTexOutId);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, desc.Width, desc.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      glBindTexture(GL_TEXTURE_2D, texDepthId);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, desc.Width, desc.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
      glBindTexture(GL_TEXTURE_2D, 0);
      glGenFramebuffers(1, &fbo);
      glBindFramebuffer(GL_FRAMEBUFFER, fbo);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shTexOutId, 0);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texDepthId, 0);
      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      if (!hDevice) {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        getOut() << "gl init error 1 " << glGetError() << std::endl;

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

        getOut() << "gl init error 2 " << glGetError() << std::endl;

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
        
        getOut() << "gl init error 3 " << glGetError() << std::endl;

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
        
        getOut() << "gl init error 4 " << glGetError() << std::endl;

        GLuint positionLocation = glGetAttribLocation(composeProgram, "position");
        if (positionLocation == -1) {
          getOut() << "compose program failed to get attrib location for 'position'" << std::endl;
          abort();
        }
        GLuint uvLocation = glGetAttribLocation(composeProgram, "uv");
        if (uvLocation == -1) {
          getOut() << "compose program failed to get attrib location for 'uv'" << std::endl;
          abort();
        }
        GLuint texLocation = glGetUniformLocation(composeProgram, "tex");
        if (texLocation == -1) {
          getOut() << "compose program failed to get uniform location for 'tex'" << std::endl;
          abort();
        }
        /* GLuint depthTexLocation = glGetUniformLocation(composeProgram, "depthTex");
        if (depthTexLocation == -1) {
          getOut() << "compose program failed to get uniform location for 'depthTex'" << std::endl;
          abort();
        } */

        getOut() << "gl init error 5 " << glGetError() << std::endl;

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

        getOut() << "gl init error 6 " << glGetError() << std::endl;

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

        getOut() << "gl init error 7 " << glGetError() << std::endl;

        GLuint indexBuffer;
        glGenBuffers(1, &indexBuffer);
        static const uint16_t indices[] = {0, 2, 1, 2, 3, 1};
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(texLocation, 0);
        
        glViewport(0, 0, desc.Width, desc.Height);
        
        getOut() << "gl init error 8 " << glGetError() << std::endl;

        hDevice = wglDXOpenDeviceNV(device.Get());
      }
      shTexInObjectHandle = wglDXRegisterObjectNV(hDevice, shTexIn, shTexInId, GL_TEXTURE_2D, WGL_ACCESS_READ_ONLY_NV);
      shTexOutObjectHandle = wglDXRegisterObjectNV(hDevice, shTexOut, shTexOutId, GL_TEXTURE_2D, WGL_ACCESS_WRITE_DISCARD_NV);
      
      getOut() << "gl init error 9 " << glGetError() << std::endl;
    }

    HANDLE objects[] = {
      shTexInObjectHandle,
      shTexOutObjectHandle
    };
    bool lockOk = wglDXLockObjectsNV(hDevice, ARRAYSIZE(objects), objects);
    if (lockOk) {
      glBindFramebuffer(GL_FRAMEBUFFER, fbo);
      glBindTexture(GL_TEXTURE_2D, shTexInId);
      glClearColor(0, 0, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
      // glFinish();
      glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_SHORT,
        (void *)0
      );
      
      auto error = glGetError();
      if (error) {
        getOut() << "gl render error " << error << std::endl;
      }

      bool unlockOk = wglDXUnlockObjectsNV(hDevice, ARRAYSIZE(objects), objects);
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
    // getOut() << "create shared 5" << std::endl;

    pTexture->handle = (void *)shTexOut;
    return vrcompositor->Submit(eEye, pTexture, pBounds, submitFlags);
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
EVRCompositorError PVRCompositor::Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags ) {
  ID3D11Texture2D *tex = reinterpret_cast<ID3D11Texture2D *>(pTexture->handle);

  getOut() << "get submit 1 " << pTexture->eType << " " << pTexture->eColorSpace << std::endl;
  if (!device) {
    tex->GetDevice(&device);
  }
  // getOut() << "get submit 2 " << device << std::endl;
  if (!context) {
    device->GetImmediateContext(&context);
  }
  // getOut() << "get submit 3 " << context << std::endl;

  ID3D11Texture2D *&shTex = eEye == Eye_Left ? shTexLeft : shTexRight;
  HANDLE &sharedHandle = eEye == Eye_Left ? shTexLeftHandle : shTexRightHandle;
  // ID3D11Texture2D *&shTex2 = eEye == Eye_Left ? shTexLeft2 : shTexRight2;
  if (!shTex) {
    D3D11_TEXTURE2D_DESC desc;
    tex->GetDesc(&desc);
    
    getOut() << "get texture desc " << (int)eEye << " " << desc.Width << " " << desc.Height << std::endl;

    // getOut() << "succ 0.1 " << desc.Width << " " << (void *)desc.BindFlags << " " << (void *)desc.MiscFlags << std::endl;
    
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;

    HRESULT hr = device->CreateTexture2D(
      &desc,
      NULL,
      &shTex
    );
    
    // getOut() << "get submit 5" << std::endl;

    if (SUCCEEDED(hr)) {
      // getOut() << "get submit 6" << std::endl;
      
      IDXGIResource *pDXGIResource;
      hr = shTex->QueryInterface(__uuidof(IDXGIResource), (void **)&pDXGIResource);
      // IDXGIResource1 *pDXGIResource;
      // HRESULT hr = tex->QueryInterface(__uuidof(IDXGIResource1), (void **)&pDXGIResource);

      if (SUCCEEDED(hr)) {
        // getOut() << "get submit 7" << std::endl;
        // getOut() << "succ 1 " << (void *)pDXGIResource << std::endl;
        hr = pDXGIResource->GetSharedHandle(&sharedHandle);
        // hr = pDXGIResource->CreateSharedHandle(NULL, DXGI_SHARED_RESOURCE_READ, L"Local\\lol", &sharedHandle);

        // getOut() << "succ 2 " << (void *)hr << " " << (void *)sharedHandle << std::endl;
        if (SUCCEEDED(hr)) {
          // getOut() << "get submit 8" << std::endl;
          // nothing
        } else {
          // getOut() << "failed to get shared texture handle: " << (void *)hr << std::endl;
          abort();
        }
      } else {
        // getOut() << "failed to get shared texture: " << (void *)hr << std::endl;
        abort();
      }
    } else {
      // getOut() << "failed to create shared texture: " << (void *)hr << std::endl;
      abort();
    }
    
    /* if (!shTex2) {
      ID3D11Resource *pD3DResource;
      HRESULT hr = device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Resource), (void**)(&pD3DResource));
      
      if (SUCCEEDED(hr)) {
        hr = pD3DResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)(&shTex2));
        
        if (SUCCEEDED(hr)) {
          // nothing
        } else {
          getOut() << "failed to unpack shared texture: " << (void *)hr << " " << (void *)sharedHandle << std::endl;
          abort();
        }

        pD3DResource->Release();
      } else {
        getOut() << "failed to unpack shared texture handle: " << (void *)hr << " " << (void *)sharedHandle << std::endl;
        abort();
      }
    } */
  }

  // getOut() << "bounds " << pBounds->uMin << " " << pBounds->uMax << " " << pBounds->vMin << " " << pBounds->vMax << std::endl;

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
  context->CopyResource(shTex, tex);

  // getOut() << "get submit 9 " << (void *)shTex << std::endl;
  
  /* Texture_t t{
    (void *)sharedHandle,
    pTexture->eType,
    pTexture->eColorSpace
  };
  return vrcompositor->Submit(eEye, &t, pBounds, nSubmitFlags); */
  
  managed_binary<Texture_t> sharedTexture(1);
  *sharedTexture.data() = Texture_t{
    (void *)sharedHandle,
    pTexture->eType,
    pTexture->eColorSpace
  };
  managed_binary<VRTextureBounds_t> bounds(1);
  *bounds.data() = *pBounds;
  return fnp.call<
    kIVRCompositor_Submit,
    EVRCompositorError,
    EVREye,
    managed_binary<Texture_t>,
    managed_binary<VRTextureBounds_t>,
    EVRSubmitFlags,
    uintptr_t
  >(eEye, std::move(sharedTexture), std::move(bounds), nSubmitFlags, (uintptr_t)device.Get());
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