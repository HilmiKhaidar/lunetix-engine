#ifndef LUNETIX_BROWSER_LUNETIX_BROWSER_PROCESS_H_
#define LUNETIX_BROWSER_LUNETIX_BROWSER_PROCESS_H_

#include "chrome/browser/browser_process.h"

namespace lunetix {

class LunetixBrowserProcess : public BrowserProcess {
 public:
  LunetixBrowserProcess();
  ~LunetixBrowserProcess() override;

  // BrowserProcess overrides:
  void StartTearDown() override;
  void PostDestroyThreads() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixBrowserProcess);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_LUNETIX_BROWSER_PROCESS_H_