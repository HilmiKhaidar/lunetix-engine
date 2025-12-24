#include "lunetix/browser/lunetix_browser_process.h"

namespace lunetix {

LunetixBrowserProcess::LunetixBrowserProcess() = default;

LunetixBrowserProcess::~LunetixBrowserProcess() = default;

void LunetixBrowserProcess::StartTearDown() {
  BrowserProcess::StartTearDown();
}

void LunetixBrowserProcess::PostDestroyThreads() {
  BrowserProcess::PostDestroyThreads();
}

}  // namespace lunetix