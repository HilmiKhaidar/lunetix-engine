#include "lunetix/browser/profiles/lunetix_profile_manager.h"

#include "chrome/browser/prefs/browser_prefs.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "lunetix/common/lunetix_constants.h"

namespace lunetix {

LunetixProfileManager::LunetixProfileManager(const base::FilePath& user_data_dir)
    : ProfileManager(user_data_dir) {}

LunetixProfileManager::~LunetixProfileManager() = default;

void LunetixProfileManager::InitProfileUserPrefs(Profile* profile) {
  ProfileManager::InitProfileUserPrefs(profile);
  
  PrefService* prefs = profile->GetPrefs();
  
  // Set Lunetix-specific default preferences
  prefs->SetString(prefs::kHomePage, kLunetixHomepageURL);
  prefs->SetBoolean(prefs::kShowHomeButton, true);
  prefs->SetBoolean(prefs::kEnableDoNotTrack, true);
  prefs->SetInteger(prefs::kDefaultSearchProviderDataVersion, 1);
}

void LunetixProfileManager::SetNonPersonalProfilePrefs(Profile* profile) {
  ProfileManager::SetNonPersonalProfilePrefs(profile);
  
  PrefService* prefs = profile->GetPrefs();
  prefs->SetString(prefs::kHomePage, kLunetixHomepageURL);
}

void LunetixProfileManager::DoFinalInitForServices(Profile* profile,
                                                  bool go_off_the_record) {
  ProfileManager::DoFinalInitForServices(profile, go_off_the_record);
}

}  // namespace lunetix