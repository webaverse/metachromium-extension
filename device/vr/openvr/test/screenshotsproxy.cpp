// #include <chrono>
#include "device/vr/openvr/test/screenshotsproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

namespace vr {
char kIVRScreenshots_RequestScreenshot[] = "Screenshots::RequestScreenshot";
char kIVRScreenshots_HookScreenshot[] = "Screenshots::HookScreenshot";
char kIVRScreenshots_GetScreenshotPropertyType[] = "Screenshots::GetScreenshotPropertyType";
char kIVRScreenshots_GetScreenshotPropertyFilename[] = "Screenshots::GetScreenshotPropertyFilename";
char kIVRScreenshots_UpdateScreenshotProgress[] = "Screenshots::UpdateScreenshotProgress";
char kIVRScreenshots_TakeStereoScreenshot[] = "Screenshots::TakeStereoScreenshot";
char kIVRScreenshots_SubmitScreenshot[] = "Screenshots::SubmitScreenshot";

PVRScreenshots::PVRScreenshots(IVRScreenshots *vrscreenshots, FnProxy &fnp) : vrscreenshots(vrscreenshots), fnp(fnp) {
  fnp.reg<
    kIVRScreenshots_RequestScreenshot,
    std::tuple<vr::EVRScreenshotError, vr::ScreenshotHandle_t>,
    vr::EVRScreenshotType,
    managed_binary<char>,
    managed_binary<char>
  >([=](vr::EVRScreenshotType type, managed_binary<char> previewFilename, managed_binary<char> vrFilename) {
    vr::ScreenshotHandle_t outScreenshotHandle;
    auto result = vrscreenshots->RequestScreenshot(&outScreenshotHandle, type, previewFilename.data(), vrFilename.data());
    return std::tuple<vr::EVRScreenshotError, vr::ScreenshotHandle_t>(
      result,
      outScreenshotHandle
    );
  });
  fnp.reg<
    kIVRScreenshots_HookScreenshot,
    vr::EVRScreenshotError,
    managed_binary<vr::EVRScreenshotType>,
    int
  >([=](managed_binary<vr::EVRScreenshotType> supportedTypes, int numTypes) {
    return vrscreenshots->HookScreenshot(supportedTypes.data(), numTypes);
  });
  fnp.reg<
    kIVRScreenshots_GetScreenshotPropertyType,
    std::tuple<vr::EVRScreenshotType, vr::EVRScreenshotError>,
    vr::ScreenshotHandle_t
  >([=](vr::ScreenshotHandle_t screenshotHandle) {
    vr::EVRScreenshotError error;
    auto result = vrscreenshots->GetScreenshotPropertyType(screenshotHandle, &error);
    return std::tuple<vr::EVRScreenshotType, vr::EVRScreenshotError>(
      result,
      error
    );
  });
  fnp.reg<
    kIVRScreenshots_GetScreenshotPropertyFilename,
    std::tuple<uint32_t, vr::EVRScreenshotError>,
    vr::ScreenshotHandle_t,
    vr::EVRScreenshotPropertyFilenames,
    managed_binary<char>,
    uint32_t
  >([=](vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, managed_binary<char> filename, uint32_t cchFilename) {
    vr::EVRScreenshotError error;
    auto result = vrscreenshots->GetScreenshotPropertyFilename(screenshotHandle, filenameType, filename.data(), cchFilename, &error);
    return std::tuple<uint32_t, vr::EVRScreenshotError>(
      result,
      error
    );
  });
  fnp.reg<
    kIVRScreenshots_UpdateScreenshotProgress,
    vr::EVRScreenshotError,
    vr::ScreenshotHandle_t,
    float
  >([=](vr::ScreenshotHandle_t screenshotHandle, float flProgress) {
    return vrscreenshots->UpdateScreenshotProgress(screenshotHandle, flProgress);
  });
  fnp.reg<
    kIVRScreenshots_TakeStereoScreenshot,
    std::tuple<vr::EVRScreenshotError, vr::ScreenshotHandle_t>,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> previewFilename, managed_binary<char> vrFilename) {
    vr::ScreenshotHandle_t screenshotHandle;
    auto result = vrscreenshots->TakeStereoScreenshot(&screenshotHandle, previewFilename.data(), vrFilename.data());
    return std::tuple<vr::EVRScreenshotError, vr::ScreenshotHandle_t>(
      result,
      screenshotHandle
    );
  });
  fnp.reg<
    kIVRScreenshots_SubmitScreenshot,
    vr::EVRScreenshotError,
    vr::ScreenshotHandle_t,
    vr::EVRScreenshotType,
    managed_binary<char>,
    managed_binary<char>
  >([=](vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, managed_binary<char> sourcePreviewFilename, managed_binary<char> sourceVRFilename) {
    return vrscreenshots->SubmitScreenshot(screenshotHandle, type, sourcePreviewFilename.data(), sourceVRFilename.data());
  });
}
vr::EVRScreenshotError PVRScreenshots::RequestScreenshot(vr::ScreenshotHandle_t *pOutScreenshotHandle, vr::EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename) {
  managed_binary<char> previewFilename(strlen(pchPreviewFilename)+1);
  memcpy(previewFilename.data(), pchPreviewFilename, previewFilename.size());
  managed_binary<char> vrFilename(strlen(pchVRFilename)+1);
  memcpy(vrFilename.data(), pchVRFilename, vrFilename.size());
  auto result = fnp.call<
    kIVRScreenshots_RequestScreenshot,
    std::tuple<vr::EVRScreenshotError, vr::ScreenshotHandle_t>,
    vr::EVRScreenshotType,
    managed_binary<char>,
    managed_binary<char>
  >(type, std::move(previewFilename), std::move(vrFilename));
  *pOutScreenshotHandle = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRScreenshotError PVRScreenshots::HookScreenshot(const vr::EVRScreenshotType *pSupportedTypes, int numTypes) {
  // getOut() << "screenshots hook client 1" << std::endl;
  managed_binary<vr::EVRScreenshotType> supportedTypes(numTypes);
  // getOut() << "screenshots hook client 2" << std::endl;
  memcpy(supportedTypes.data(), pSupportedTypes, numTypes * sizeof(vr::EVRScreenshotType));
  // getOut() << "screenshots hook client 3" << std::endl;
  auto result = fnp.call<
    kIVRScreenshots_HookScreenshot,
    vr::EVRScreenshotError,
    managed_binary<vr::EVRScreenshotType>,
    int
  >(std::move(supportedTypes), numTypes);
  // getOut() << "screenshots hook client 4 " << result << std::endl;
  return result;
}
vr::EVRScreenshotType PVRScreenshots::GetScreenshotPropertyType(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotError *pError) {
  auto result = fnp.call<
    kIVRScreenshots_GetScreenshotPropertyType,
    std::tuple<vr::EVRScreenshotType, vr::EVRScreenshotError>,
    vr::ScreenshotHandle_t
  >(screenshotHandle);
  if (pError) {
    *pError = std::get<1>(result);
  }
  return std::get<0>(result);
}
uint32_t PVRScreenshots::GetScreenshotPropertyFilename(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, char *pchFilename, uint32_t cchFilename, vr::EVRScreenshotError *pError) {
  managed_binary<char> filename(cchFilename);
  memcpy(filename.data(), pchFilename, cchFilename);
  auto result = fnp.call<
    kIVRScreenshots_GetScreenshotPropertyFilename,
    std::tuple<uint32_t, vr::EVRScreenshotError>,
    vr::ScreenshotHandle_t,
    vr::EVRScreenshotPropertyFilenames,
    managed_binary<char>,
    uint32_t
  >(screenshotHandle, filenameType, std::move(filename), cchFilename);
  if (pError) {
    *pError = std::get<1>(result);
  }
  return std::get<0>(result);
}
vr::EVRScreenshotError PVRScreenshots::UpdateScreenshotProgress(vr::ScreenshotHandle_t screenshotHandle, float flProgress) {
  return fnp.call<
    kIVRScreenshots_UpdateScreenshotProgress,
    vr::EVRScreenshotError,
    vr::ScreenshotHandle_t,
    float
  >(screenshotHandle, flProgress);
}
vr::EVRScreenshotError PVRScreenshots::TakeStereoScreenshot(vr::ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename) {
  managed_binary<char> previewFilename(strlen(pchPreviewFilename)+1);
  memcpy(previewFilename.data(), pchPreviewFilename, previewFilename.size());
  managed_binary<char> vrFilename(strlen(pchVRFilename)+1);
  memcpy(vrFilename.data(), pchVRFilename, vrFilename.size());
  auto result = fnp.call<
    kIVRScreenshots_TakeStereoScreenshot,
    std::tuple<vr::EVRScreenshotError, vr::ScreenshotHandle_t>,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(previewFilename), std::move(vrFilename));
  *pOutScreenshotHandle = std::get<1>(result);
  return std::get<0>(result);
}
vr::EVRScreenshotError PVRScreenshots::SubmitScreenshot(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename) {
  managed_binary<char> sourcePreviewFilename(strlen(pchSourcePreviewFilename)+1);
  memcpy(sourcePreviewFilename.data(), pchSourcePreviewFilename, sourcePreviewFilename.size());
  managed_binary<char> sourceVrFilename(strlen(pchSourceVRFilename)+1);
  memcpy(sourceVrFilename.data(), pchSourceVRFilename, sourceVrFilename.size());
  return fnp.call<
    kIVRScreenshots_SubmitScreenshot,
    vr::EVRScreenshotError,
    ScreenshotHandle_t,
    vr::EVRScreenshotType,
    managed_binary<char>,
    managed_binary<char>
  >(screenshotHandle, type, std::move(sourcePreviewFilename), std::move(sourceVrFilename));
}
}