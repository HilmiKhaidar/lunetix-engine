#ifndef LUNETIX_BROWSER_PREFS_LUNETIX_PREF_SERVICE_H_
#define LUNETIX_BROWSER_PREFS_LUNETIX_PREF_SERVICE_H_

#include "components/prefs/pref_service.h"

namespace lunetix {

class LunetixPrefService {
 public:
  static void RegisterLunetixPrefs(PrefRegistrySimple* registry);
  static void SetLunetixDefaults(PrefService* prefs);
  
  // Lunetix-specific preference keys
  static const char kLunetixHomePage[];
  static const char kLunetixShowHomeButton[];
  static const char kLunetixBlockTrackers[];
  static const char kLunetixEnableAdBlock[];
  static const char kLunetixPrivacyMode[];
  static const char kLunetixUpdateChannel[];
  static const char kLunetixTelemetryEnabled[];
  static const char kLunetixCustomUserAgent[];
  static const char kLunetixSearchEngine[];
  static const char kLunetixDownloadDirectory[];
  static const char kLunetixStartupAction[];
  static const char kLunetixNewTabPage[];
  static const char kLunetixTheme[];
  static const char kLunetixLanguage[];
  static const char kLunetixProxySettings[];
  static const char kLunetixSecurityLevel[];

 private:
  LunetixPrefService() = delete;
  ~LunetixPrefService() = delete;
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_PREFS_LUNETIX_PREF_SERVICE_H_