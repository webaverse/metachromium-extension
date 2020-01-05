#ifndef _openvr_settingsproxy_h_
#define _openvr_settingsproxy_h_

// #include <D3D11_1.h>
// #include <DXGI1_4.h>
// #include <wrl.h>

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"
// #include "device/vr/openvr/test/glcontext.h"
#include "device/vr/openvr/test/fnproxy.h"

namespace vr {
class PVRSettings : public IVRSettings {
public:
  IVRSettings *vrsettings;
  FnProxy &fnp;

  PVRSettings(IVRSettings *vrsettings, FnProxy &fnp);
  virtual const char *GetSettingsErrorNameFromEnum(EVRSettingsError eError);
  virtual bool Sync(bool bForce = false, EVRSettingsError *peError = nullptr);
  virtual void SetBool(const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError = nullptr);
  virtual void SetInt32(const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError = nullptr);
  virtual void SetFloat(const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError = nullptr);
  virtual void SetString(const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError = nullptr);
  virtual bool GetBool(const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr);
  virtual int32_t GetInt32(const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr);
  virtual float GetFloat(const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr);
  virtual void GetString(const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError = nullptr);
  virtual void RemoveSection(const char *pchSection, EVRSettingsError *peError = nullptr);
  virtual void RemoveKeyInSection(const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr);
};
}

#endif