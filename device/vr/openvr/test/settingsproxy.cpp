// #include <chrono>
#include "device/vr/openvr/test/settingsproxy.h"
#include "device/vr/openvr/test/fake_openvr_impl_api.h"

// using namespace vr;

namespace vr {
char kIVRSettings_GetSettingsErrorNameFromEnum[] = "Settings::GetSettingsErrorNameFromEnum";
char kIVRSettings_Sync[] = "Settings::Sync";
char kIVRSettings_SetBool[] = "Settings::SetBool";
char kIVRSettings_SetInt32[] = "Settings::SetInt32";
char kIVRSettings_SetFloat[] = "Settings::SetFloat";
char kIVRSettings_SetString[] = "Settings::SetString";
char kIVRSettings_GetBool[] = "Settings::GetBool";
char kIVRSettings_GetInt32[] = "Settings::GetInt32";
char kIVRSettings_GetFloat[] = "Settings::GetFloat";
char kIVRSettings_GetString[] = "Settings::GetString";
char kIVRSettings_RemoveSection[] = "Settings::RemoveSection";
char kIVRSettings_RemoveKeyInSection[] = "Settings::RemoveKeyInSection";

PVRSettings::PVRSettings(IVRSettings *vrsettings, FnProxy &fnp) : vrsettings(vrsettings), fnp(fnp) {
  // getOut() << "settings init 1" << std::endl;
  fnp.reg<
    kIVRSettings_GetSettingsErrorNameFromEnum,
    int
  >([=]() {
    getOut() << "GetSettingsErrorNameFromEnum abort" << std::endl;
    abort();
    // getOut() << "set action manifest path" << actionManifestPath.data() << std::endl;
    // return vrinput->SetActionManifestPath(actionManifestPath.data());
    return 0;
  });
  fnp.reg<
    kIVRSettings_Sync,
    std::tuple<bool, EVRSettingsError>,
    bool
  >([=](bool bForce) {
    // getOut() << "set action manifest path" << actionManifestPath.data() << std::endl;
    // return vrinput->SetActionManifestPath(actionManifestPath.data());
    EVRSettingsError error;
    auto result = vrsettings->Sync(bForce, &error);
    return std::tuple<bool, EVRSettingsError>(
      result,
      error
    );
  });
  fnp.reg<
    kIVRSettings_SetBool,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>,
    bool
  >([=](managed_binary<char> section, managed_binary<char> settingsKey, bool bValue) {
    EVRSettingsError error;
    vrsettings->SetBool(section.data(), settingsKey.data(), bValue, &error);
    return error;
  });
  fnp.reg<
    kIVRSettings_SetInt32,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>,
    int32_t
  >([=](managed_binary<char> section, managed_binary<char> settingsKey, int32_t nValue) {
    EVRSettingsError error;
    vrsettings->SetInt32(section.data(), settingsKey.data(), nValue, &error);
    return error;
  });
  fnp.reg<
    kIVRSettings_SetFloat,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>,
    float
  >([=](managed_binary<char> section, managed_binary<char> settingsKey, float flValue) {
    EVRSettingsError error;
    vrsettings->SetFloat(section.data(), settingsKey.data(), flValue, &error);
    return error;
  });
  fnp.reg<
    kIVRSettings_SetString,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>,
     managed_binary<char>
  >([=](managed_binary<char> section, managed_binary<char> settingsKey, managed_binary<char> value) {
    EVRSettingsError error;
    vrsettings->SetString(section.data(), settingsKey.data(), value.data(), &error);
    return error;
  });
  fnp.reg<
    kIVRSettings_GetBool,
    std::tuple<bool, EVRSettingsError>,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> section, managed_binary<char> settingsKey) {
    EVRSettingsError error;
    auto result = vrsettings->GetBool(section.data(), settingsKey.data(), &error);
    return std::tuple<bool, EVRSettingsError>(
      result,
      error
    );
  });
  fnp.reg<
    kIVRSettings_GetInt32,
    std::tuple<int32_t, EVRSettingsError>,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> section, managed_binary<char> settingsKey) {
    EVRSettingsError error;
    auto result = vrsettings->GetInt32(section.data(), settingsKey.data(), &error);
    return std::tuple<int32_t, EVRSettingsError>(
      result,
      error
    );
  });
  fnp.reg<
    kIVRSettings_GetFloat,
    std::tuple<float, EVRSettingsError>,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> section, managed_binary<char> settingsKey) {
    EVRSettingsError error;
    auto result = vrsettings->GetFloat(section.data(), settingsKey.data(), &error);
    return std::tuple<float, EVRSettingsError>(
      result,
      error
    );
  });
  fnp.reg<
    kIVRSettings_GetString,
    std::tuple<managed_binary<char>, EVRSettingsError>,
    managed_binary<char>,
    managed_binary<char>,
    uint32_t
  >([=](managed_binary<char> section, managed_binary<char> settingsKey, uint32_t unValueLen) {
    managed_binary<char> value(unValueLen);
    EVRSettingsError error;
    vrsettings->GetString(section.data(), settingsKey.data(), value.data(), unValueLen, &error);
    return std::tuple<managed_binary<char>, EVRSettingsError>(
      std::move(value),
      error
    );
  });
  fnp.reg<
    kIVRSettings_RemoveSection,
    EVRSettingsError,
    managed_binary<char>
  >([=](managed_binary<char> section) {
    EVRSettingsError error;
    vrsettings->RemoveSection(section.data(), &error);
    return error;
  });
  fnp.reg<
    kIVRSettings_RemoveKeyInSection,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>
  >([=](managed_binary<char> section, managed_binary<char> settingsKey) {
    EVRSettingsError error;
    vrsettings->RemoveKeyInSection(section.data(), settingsKey.data(), &error);
    return error;
  });
  // getOut() << "settings init 2" << std::endl;
}
const char *PVRSettings::GetSettingsErrorNameFromEnum(EVRSettingsError eError) {
  getOut() << "GetSettingsErrorNameFromEnum abort" << std::endl; abort();
  return "";
}
bool PVRSettings::Sync(bool bForce, EVRSettingsError *peError) {
  auto result = fnp.call<
    kIVRSettings_Sync,
    std::tuple<bool, EVRSettingsError>,
    bool
  >(bForce);
  if (peError) {
    *peError = std::get<1>(result);
  }
  return std::get<0>(result);
}
void PVRSettings::SetBool(const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  auto result = fnp.call<
    kIVRSettings_SetBool,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>,
    bool
  >(std::move(section), std::move(settingsKey), bValue);
  if (peError) {
    *peError = result;
  }
}
void PVRSettings::SetInt32(const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  auto result = fnp.call<
    kIVRSettings_SetInt32,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>,
    int32_t
  >(std::move(section), std::move(settingsKey), nValue);
  if (peError) {
    *peError = result;
  }
}
void PVRSettings::SetFloat(const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  auto result = fnp.call<
    kIVRSettings_SetFloat,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>,
    float
  >(std::move(section), std::move(settingsKey), flValue);
  if (peError) {
    *peError = result;
  }
}
void PVRSettings::SetString(const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  managed_binary<char> value(strlen(pchValue)+1);
  memcpy(value.data(), pchValue, value.size());
  auto result = fnp.call<
    kIVRSettings_SetString,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(section), std::move(settingsKey), std::move(value));
  if (peError) {
    *peError = result;
  }
}
bool PVRSettings::GetBool(const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  auto result = fnp.call<
    kIVRSettings_GetBool,
    std::tuple<bool, EVRSettingsError>,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(section), std::move(settingsKey));
  if (peError) {
    *peError = std::get<1>(result);
  }
  return std::get<0>(result);
}
int32_t PVRSettings::GetInt32(const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  auto result = fnp.call<
    kIVRSettings_GetInt32,
    std::tuple<int32_t, EVRSettingsError>,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(section), std::move(settingsKey));
  if (peError) {
    *peError = std::get<1>(result);
  }
  return std::get<0>(result);
}
float PVRSettings::GetFloat(const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  auto result = fnp.call<
    kIVRSettings_GetFloat,
    std::tuple<float, EVRSettingsError>,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(section), std::move(settingsKey));
  if (peError) {
    *peError = std::get<1>(result);
  }
  return std::get<0>(result);
}
void PVRSettings::GetString(const char *pchSection, const char *pchSettingsKey, VR_OUT_STRING() char *pchValue, uint32_t unValueLen, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  auto result = fnp.call<
    kIVRSettings_GetString,
    std::tuple<managed_binary<char>, EVRSettingsError>,
    managed_binary<char>,
    managed_binary<char>,
    uint32_t
  >(std::move(section), std::move(settingsKey), unValueLen);
  if (peError) {
    *peError = std::get<1>(result);
  }
  memcpy(pchValue, std::get<0>(result).data(), std::get<0>(result).size());
}
void PVRSettings::RemoveSection(const char *pchSection, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  auto result = fnp.call<
    kIVRSettings_RemoveSection,
    EVRSettingsError,
    managed_binary<char>
  >(std::move(section));
  if (peError) {
    *peError = result;
  }
}
void PVRSettings::RemoveKeyInSection(const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError) {
  managed_binary<char> section(strlen(pchSection)+1);
  memcpy(section.data(), pchSection, section.size());
  managed_binary<char> settingsKey(strlen(pchSettingsKey)+1);
  memcpy(settingsKey.data(), pchSettingsKey, settingsKey.size());
  auto result = fnp.call<
    kIVRSettings_RemoveKeyInSection,
    EVRSettingsError,
    managed_binary<char>,
    managed_binary<char>
  >(std::move(section), std::move(settingsKey));
  if (peError) {
    *peError = result;
  }
}
}