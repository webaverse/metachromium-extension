#include "stdafx.h"
#define BASE_IMPL
#include "BaseExtendedDisplay.h"

// #include "libovr_wrapper.h"
// #include "OVR_CAPI.h"
#include <string>

using namespace vr;

// Unreal Engine uses this for some silly reason
void BaseExtendedDisplay::GetWindowBounds(int32_t * pnX, int32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight) {
  TRACE("BaseExtendedDisplay", []() { getOut() << "BaseExtendedDisplay::GetWindowBounds" << std::endl; });
	g_vrextendeddisplay->GetWindowBounds(pnX, pnY, pnWidth, pnHeight);
}

void BaseExtendedDisplay::GetEyeOutputViewport(vr::EVREye eEye, uint32_t * pnX, uint32_t * pnY, uint32_t * pnWidth, uint32_t * pnHeight) {
  TRACE("BaseExtendedDisplay", []() { getOut() << "BaseExtendedDisplay::GetEyeOutputViewport" << std::endl; });
	g_vrextendeddisplay->GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight);
}

void BaseExtendedDisplay::GetDXGIOutputInfo(int32_t * pnAdapterIndex, int32_t * pnAdapterOutputIndex) {
  TRACE("BaseExtendedDisplay", []() { getOut() << "BaseExtendedDisplay::GetDXGIOutputInfo" << std::endl; });
	g_vrextendeddisplay->GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex);
}
