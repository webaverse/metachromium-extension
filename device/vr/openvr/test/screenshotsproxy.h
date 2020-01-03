#ifndef _openvr_screenshotsproxy_h_
#define _openvr_screenshotsproxy_h_

// #include <D3D11_1.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
// #include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRScreenshots : public IVRScreenshots {
public:
  IVRScreenshots *vrscreenshots;
  FnProxy &fnp;

  PVRScreenshots(IVRScreenshots *vrscreenshots, FnProxy &fnp);
	virtual vr::EVRScreenshotError RequestScreenshot(vr::ScreenshotHandle_t *pOutScreenshotHandle, vr::EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename);
	virtual vr::EVRScreenshotError HookScreenshot(const vr::EVRScreenshotType *pSupportedTypes, int numTypes);
	virtual vr::EVRScreenshotType GetScreenshotPropertyType(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotError *pError);
	virtual uint32_t GetScreenshotPropertyFilename(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotPropertyFilenames filenameType, char *pchFilename, uint32_t cchFilename, vr::EVRScreenshotError *pError);
	virtual vr::EVRScreenshotError UpdateScreenshotProgress(vr::ScreenshotHandle_t screenshotHandle, float flProgress);
	virtual vr::EVRScreenshotError TakeStereoScreenshot(vr::ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename);
	virtual vr::EVRScreenshotError SubmitScreenshot(vr::ScreenshotHandle_t screenshotHandle, vr::EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename);
};
}

#endif