# Set the Windows kit if using MSVC
# CMake will look for the newest kit that isn't newer than this
# Required to find modern D3D12 header

cmake_minimum_required(VERSION 3.12)
project(OpenVrHook)

INCLUDE_DIRECTORIES(
  ../..
  ../../third_party/openvr/src/headers
  ../../third_party/skia
  sample
  OpenOVR
  SplitOpenVRHeaders
  gl/include
  gl/include/glew
  # gl/include/glad
  gl/include/KHR
  gl/include/GLFW
  ../../third_party/khronos
  detours
)
LINK_DIRECTORIES(
  gl/lib/glew
  gl/lib/glfw
  ../../third_party/openvr/src/bin/win64
  ../../third_party/openvr/src/lib/win64
)

SET(src
  openvr/test/fake_openvr_impl_api.cc
  openvr/test/glcontext.cpp
  openvr/test/serializer.cpp
  openvr/test/coreproxy.cpp
  openvr/test/systemproxy.cpp
  openvr/test/compositorproxy.cpp
  openvr/test/inputproxy.cpp
  openvr/test/screenshotsproxy.cpp
  openvr/test/chaperoneproxy.cpp
  openvr/test/chaperonesetupproxy.cpp
  openvr/test/settingsproxy.cpp
  openvr/test/rendermodelsproxy.cpp
  openvr/test/applicationsproxy.cpp
  openvr/test/overlayproxy.cpp
  openvr/test/fnproxy.cpp
  openvr/test/compositor2d.cpp
  # openvr/test/test_helper.cc
  # openvr/test/test_helper.h
  # test/test_hook.h
  # sample/hellovr_opengl_main.cpp
  # sample/shared/Matrices.cpp
  OpenOVR/Reimpl/stubs.gen.cpp
  OpenOVR/Reimpl/BaseCompositor.cpp
  OpenOVR/Reimpl/CVRCompositor.cpp
  OpenOVR/Reimpl/BaseSystem.cpp
  OpenOVR/Reimpl/CVRSystem.cpp
  OpenOVR/Reimpl/BaseChaperone.cpp
  OpenOVR/Reimpl/CVRChaperone.cpp
  OpenOVR/Reimpl/BaseChaperoneSetup.cpp
  OpenOVR/Reimpl/CVRChaperone.cpp
  OpenOVR/Reimpl/BaseOverlay.cpp
  OpenOVR/Reimpl/CVROverlay.cpp
  OpenOVR/Reimpl/BaseRenderModels.cpp
  OpenOVR/Reimpl/CVRRenderModels.cpp
  OpenOVR/Reimpl/BaseScreenshots.cpp
  OpenOVR/Reimpl/CVRScreenshots.cpp
  OpenOVR/Reimpl/BaseSettings.cpp
  OpenOVR/Reimpl/CVRSettings.cpp
  OpenOVR/Reimpl/BaseExtendedDisplay.cpp
  OpenOVR/Reimpl/CVRExtendedDisplay.cpp
  OpenOVR/Reimpl/BaseApplications.cpp
  OpenOVR/Reimpl/CVRApplications.cpp
  OpenOVR/Reimpl/BaseInput.cpp
  OpenOVR/Reimpl/CVRInput.cpp
  OpenOVR/Reimpl/BaseClientCore.cpp
  OpenOVR/Reimpl/CVRClientCore.cpp
  ../../third_party/openvr/src/src/vrcommon/sharedlibtools_public.cpp
  detours/detours.cpp
  detours/disasm.cpp
  detours/modules.cpp
  detours/image.cpp
  openvr/test/hijack.cc
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
ADD_LIBRARY(vrclient_x64 SHARED ${src} openvr/test/dll.cc)
# target_link_libraries(vrclient_x64 openvr_api.dll)
target_link_libraries(vrclient_x64 dxgi.lib d3d11.lib d3dcompiler.lib dxguid.lib opengl32.lib glew32.lib glfw3.lib)
set_property(TARGET vrclient_x64 PROPERTY CXX_STANDARD 17)
set_property(TARGET vrclient_x64 PROPERTY CXX_STANDARD_REQUIRED ON)

ADD_EXECUTABLE(process WIN32 ${src} openvr/test/process.cpp)
target_link_libraries(process dxgi.lib d3d11.lib d3dcompiler.lib dxguid.lib opengl32.lib glew32.lib glfw3.lib)
set_property(TARGET process PROPERTY CXX_STANDARD 17)
set_property(TARGET process PROPERTY CXX_STANDARD_REQUIRED ON)

ADD_EXECUTABLE(process3 WIN32 ${src} openvr/test/process3.cpp)
target_link_libraries(process3 dxgi.lib d3d11.lib d3dcompiler.lib dxguid.lib opengl32.lib glew32.lib glfw3.lib)
set_property(TARGET process3 PROPERTY CXX_STANDARD 17)
set_property(TARGET process3 PROPERTY CXX_STANDARD_REQUIRED ON)

add_definitions(-D_USE_MATH_DEFINES)
add_definitions(-DNOMINMAX)