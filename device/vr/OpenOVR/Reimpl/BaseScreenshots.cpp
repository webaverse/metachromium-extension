#include "stdafx.h"
#define BASE_IMPL
#include "BaseScreenshots.h"
#include <string>

using namespace vr;

EVRScreenshotError BaseScreenshots::RequestScreenshot(ScreenshotHandle_t *pOutScreenshotHandle, EVRScreenshotType type, const char *pchPreviewFilename, const char *pchVRFilename) {
	return g_pvrscreenshots->RequestScreenshot(pOutScreenshotHandle, type, pchPreviewFilename, pchVRFilename);
}
EVRScreenshotError BaseScreenshots::HookScreenshot(VR_ARRAY_COUNT(numTypes) const EVRScreenshotType *pSupportedTypes, int numTypes) {
	return g_pvrscreenshots->HookScreenshot(pSupportedTypes, numTypes);
}
EVRScreenshotType BaseScreenshots::GetScreenshotPropertyType(ScreenshotHandle_t screenshotHandle, EVRScreenshotError *pError) {
	return g_pvrscreenshots->GetScreenshotPropertyType(screenshotHandle, pError);
}
uint32_t BaseScreenshots::GetScreenshotPropertyFilename(ScreenshotHandle_t screenshotHandle, EVRScreenshotPropertyFilenames filenameType, VR_OUT_STRING() char *pchFilename, uint32_t cchFilename, EVRScreenshotError *pError) {
	return g_pvrscreenshots->GetScreenshotPropertyFilename(screenshotHandle, filenameType, pchFilename, cchFilename, pError);
}
EVRScreenshotError BaseScreenshots::UpdateScreenshotProgress(ScreenshotHandle_t screenshotHandle, float flProgress) {
	return g_pvrscreenshots->UpdateScreenshotProgress(screenshotHandle, flProgress);
}
EVRScreenshotError BaseScreenshots::TakeStereoScreenshot(ScreenshotHandle_t *pOutScreenshotHandle, const char *pchPreviewFilename, const char *pchVRFilename) {
	return g_pvrscreenshots->TakeStereoScreenshot(pOutScreenshotHandle, pchPreviewFilename, pchVRFilename);
}
EVRScreenshotError BaseScreenshots::SubmitScreenshot(ScreenshotHandle_t screenshotHandle, EVRScreenshotType type, const char *pchSourcePreviewFilename, const char *pchSourceVRFilename) {
	return g_pvrscreenshots->SubmitScreenshot(screenshotHandle, type, pchSourcePreviewFilename, pchSourceVRFilename);
}
