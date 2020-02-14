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
  ../../opencv/include
)
LINK_DIRECTORIES(
  gl/lib/glew
  gl/lib/glfw
  ../../third_party/openvr/src/bin/win64
  ../../third_party/openvr/src/lib/win64
  ../../opencv/x64/vc16/lib
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
  openvr/test/matrix.cpp
  openvr/test/compositor2d.cpp
  openvr/test/qr.cpp
  openvr/test/cv.cpp
)

set(OPENCV_LIBS
  opencv_aruco420.lib
  opencv_bgsegm420.lib
  opencv_bioinspired420.lib
  opencv_calib3d420.lib
  opencv_ccalib420.lib
  opencv_core420.lib
  opencv_datasets420.lib
  opencv_dnn420.lib
  opencv_dnn_objdetect420.lib
  opencv_dnn_superres420.lib
  opencv_dpm420.lib
  opencv_face420.lib
  opencv_features2d420.lib
  opencv_flann420.lib
  opencv_fuzzy420.lib
  opencv_gapi420.lib
  opencv_hfs420.lib
  opencv_highgui420.lib
  opencv_img_hash420.lib
  opencv_imgcodecs420.lib
  opencv_imgproc420.lib
  opencv_intensity_transform420.lib
  opencv_line_descriptor420.lib
  opencv_ml420.lib
  opencv_objdetect420.lib
  opencv_optflow420.lib
  opencv_phase_unwrapping420.lib
  opencv_photo420.lib
  opencv_plot420.lib
  opencv_quality420.lib
  opencv_rapid420.lib
  opencv_reg420.lib
  opencv_rgbd420.lib
  opencv_saliency420.lib
  opencv_shape420.lib
  opencv_stereo420.lib
  opencv_stitching420.lib
  opencv_structured_light420.lib
  opencv_superres420.lib
  opencv_surface_matching420.lib
  opencv_text420.lib
  opencv_tracking420.lib
  opencv_video420.lib
  opencv_videoio420.lib
  opencv_videostab420.lib
  opencv_xfeatures2d420.lib
  opencv_ximgproc420.lib
  opencv_xobjdetect420.lib
  opencv_xphoto420.lib
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/mock_vr_clients/bin)
ADD_LIBRARY(vrclient_x64 SHARED ${src} openvr/test/dll.cc)
target_link_libraries(vrclient_x64 dxgi.lib d3d11.lib d3dcompiler.lib dxguid.lib opengl32.lib glew32.lib glfw3.lib ${OPENCV_LIBS})
set_property(TARGET vrclient_x64 PROPERTY CXX_STANDARD 17)
set_property(TARGET vrclient_x64 PROPERTY CXX_STANDARD_REQUIRED ON)

ADD_EXECUTABLE(process WIN32 ${src} openvr/test/process.cpp)
target_link_libraries(process dxgi.lib d3d11.lib d3dcompiler.lib dxguid.lib opengl32.lib glew32.lib glfw3.lib ${OPENCV_LIBS})
set_property(TARGET process PROPERTY CXX_STANDARD 17)
set_property(TARGET process PROPERTY CXX_STANDARD_REQUIRED ON)

ADD_EXECUTABLE(add_hook WIN32 ${src} openvr/test/process3.cpp)
target_link_libraries(add_hook dxgi.lib d3d11.lib d3dcompiler.lib dxguid.lib opengl32.lib glew32.lib glfw3.lib ${OPENCV_LIBS})
set_property(TARGET add_hook PROPERTY CXX_STANDARD 17)
set_property(TARGET add_hook PROPERTY CXX_STANDARD_REQUIRED ON)

ADD_EXECUTABLE(native_host ${src} openvr/test/process4.cpp)
target_link_libraries(native_host dxgi.lib d3d11.lib d3dcompiler.lib dxguid.lib opengl32.lib glew32.lib glfw3.lib ${OPENCV_LIBS})
set_property(TARGET native_host PROPERTY CXX_STANDARD 17)
set_property(TARGET native_host PROPERTY CXX_STANDARD_REQUIRED ON)

add_definitions(-D_USE_MATH_DEFINES)
add_definitions(-DNOMINMAX)