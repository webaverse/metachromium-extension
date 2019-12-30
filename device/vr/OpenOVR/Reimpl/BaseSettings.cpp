#include "stdafx.h"
#define BASE_IMPL
#include "BaseSettings.h"
#include "OpenVR/interfaces/IVRSettings_001.h"
#include "OpenVR/interfaces/IVRSettings_002.h"
#include "Misc/Config.h"
#include "BaseSystem.h"
#include <string>
#include <codecvt>

// #include "OVR_CAPI_Audio.h"

using namespace std;
namespace kk1 = vr::IVRSettings_001;
namespace kk = vr::IVRSettings_002;

const char * BaseSettings::GetSettingsErrorNameFromEnum(EVRSettingsError eError) {
  return g_vrsettings->GetSettingsErrorNameFromEnum(eError);
}
bool  BaseSettings::Sync(bool bForce, EVRSettingsError * peError) {
	return g_vrsettings->Sync(bForce, peError);
}
void  BaseSettings::SetBool(const char * pchSection, const char * pchSettingsKey, bool bValue, EVRSettingsError * peError) {
	return g_vrsettings->SetBool(pchSection, pchSettingsKey, bValue, peError);
}
void  BaseSettings::SetInt32(const char * pchSection, const char * pchSettingsKey, int32_t nValue, EVRSettingsError * peError) {
	return g_vrsettings->SetInt32(pchSection, pchSettingsKey, nValue, peError);
}
void  BaseSettings::SetFloat(const char * pchSection, const char * pchSettingsKey, float flValue, EVRSettingsError * peError) {
	return g_vrsettings->SetFloat(pchSection, pchSettingsKey, flValue, peError);
}
void  BaseSettings::SetString(const char * pchSection, const char * pchSettingsKey, const char * pchValue, EVRSettingsError * peError) {
	return g_vrsettings->SetString(pchSection, pchSettingsKey, pchValue, peError);
}
bool  BaseSettings::GetBool(const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError) {
	return g_vrsettings->GetBool(pchSection, pchSettingsKey, peError);
}
int32_t  BaseSettings::GetInt32(const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError) {
	return g_vrsettings->GetInt32(pchSection, pchSettingsKey, peError);
}
float  BaseSettings::GetFloat(const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError) {
	return g_vrsettings->GetFloat(pchSection, pchSettingsKey, peError);
}
void  BaseSettings::GetString(const char * pchSection, const char * pchSettingsKey, VR_OUT_STRING() char * pchValue,
	   uint32_t unValueLen, EVRSettingsError * peError) {
  return g_vrsettings->GetString(pchSection, pchSettingsKey, pchValue, unValueLen, peError);
}
void  BaseSettings::RemoveSection(const char * pchSection, EVRSettingsError * peError) {
	return g_vrsettings->RemoveSection(pchSection, peError);
}
void  BaseSettings::RemoveKeyInSection(const char * pchSection, const char * pchSettingsKey, EVRSettingsError * peError) {
	return g_vrsettings->RemoveKeyInSection(pchSection, pchSettingsKey, peError);
}
