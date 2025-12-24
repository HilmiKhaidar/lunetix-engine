#ifndef LUNETIX_APP_LUNETIX_MAIN_DELEGATE_H_
#define LUNETIX_APP_LUNETIX_MAIN_DELEGATE_H_

#include "base/time/time.h"
#include "chrome/app/chrome_main_delegate.h"

namespace lunetix {

class LunetixMainDelegate : public ChromeMainDelegate {
 public:
  explicit LunetixMainDelegate(base::TimeTicks exe_entry_point_ticks);
  ~LunetixMainDelegate() override;

  // ChromeMainDelegate overrides:
  std::optional<int> BasicStartupComplete() override;
  void PreSandboxStartup() override;
  std::optional<int> PreBrowserMain() override;
  std::optional<int> PostEarlyInitialization(InvokedIn invoked_in) override;

 protected:
  // ChromeMainDelegate overrides:
  content::ContentBrowserClient* CreateContentBrowserClient() override;
  content::ContentRendererClient* CreateContentRendererClient() override;
  content::ContentUtilityClient* CreateContentUtilityClient() override;

 private:
  base::TimeTicks exe_entry_point_ticks_;
};

}  // namespace lunetix

#endif  // LUNETIX_APP_LUNETIX_MAIN_DELEGATE_H_