#ifndef LUNETIX_BROWSER_LUNETIX_BROWSER_MAIN_PARTS_H_
#define LUNETIX_BROWSER_LUNETIX_BROWSER_MAIN_PARTS_H_

#include "chrome/browser/chrome_browser_main.h"

namespace lunetix {

class LunetixBrowserMainParts : public ChromeBrowserMainParts {
 public:
  explicit LunetixBrowserMainParts(bool is_integration_test);
  ~LunetixBrowserMainParts() override;

  // ChromeBrowserMainParts overrides:
  int PreEarlyInitialization() override;
  void PostEarlyInitialization() override;
  void PreMainMessageLoopStart() override;
  void PostMainMessageLoopStart() override;
  int PreCreateThreads() override;
  void PostCreateThreads() override;
  int PreMainMessageLoopRun() override;
  void PostMainMessageLoopRun() override;
  void PostDestroyThreads() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixBrowserMainParts);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_LUNETIX_BROWSER_MAIN_PARTS_H_