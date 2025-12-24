#ifndef LUNETIX_BROWSER_PROFILES_LUNETIX_PROFILE_MANAGER_H_
#define LUNETIX_BROWSER_PROFILES_LUNETIX_PROFILE_MANAGER_H_

#include "chrome/browser/profiles/profile_manager.h"

namespace lunetix {

class LunetixProfileManager : public ProfileManager {
 public:
  explicit LunetixProfileManager(const base::FilePath& user_data_dir);
  ~LunetixProfileManager() override;

  // ProfileManager overrides:
  void InitProfileUserPrefs(Profile* profile) override;
  void SetNonPersonalProfilePrefs(Profile* profile) override;

 protected:
  void DoFinalInitForServices(Profile* profile,
                             bool go_off_the_record) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixProfileManager);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_PROFILES_LUNETIX_PROFILE_MANAGER_H_