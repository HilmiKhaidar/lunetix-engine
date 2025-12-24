#include "lunetix/browser/lunetix_browser_main_parts.h"

#include "base/bind.h"
#include "base/command_line.h"
#include "base/path_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "chrome/common/chrome_paths.h"
#include "lunetix/browser/lunetix_browser_process.h"
#include "lunetix/common/lunetix_paths.h"

namespace lunetix {

LunetixBrowserMainParts::LunetixBrowserMainParts(bool is_integration_test)
    : ChromeBrowserMainParts(is_integration_test) {}

LunetixBrowserMainParts::~LunetixBrowserMainParts() = default;

int LunetixBrowserMainParts::PreEarlyInitialization() {
  return ChromeBrowserMainParts::PreEarlyInitialization();
}

void LunetixBrowserMainParts::PostEarlyInitialization() {
  ChromeBrowserMainParts::PostEarlyInitialization();
}

void LunetixBrowserMainParts::PreMainMessageLoopStart() {
  ChromeBrowserMainParts::PreMainMessageLoopStart();
}

void LunetixBrowserMainParts::PostMainMessageLoopStart() {
  ChromeBrowserMainParts::PostMainMessageLoopStart();
}

int LunetixBrowserMainParts::PreCreateThreads() {
  return ChromeBrowserMainParts::PreCreateThreads();
}

void LunetixBrowserMainParts::PostCreateThreads() {
  ChromeBrowserMainParts::PostCreateThreads();
}

int LunetixBrowserMainParts::PreMainMessageLoopRun() {
  return ChromeBrowserMainParts::PreMainMessageLoopRun();
}

void LunetixBrowserMainParts::PostMainMessageLoopRun() {
  ChromeBrowserMainParts::PostMainMessageLoopRun();
}

void LunetixBrowserMainParts::PostDestroyThreads() {
  ChromeBrowserMainParts::PostDestroyThreads();
}

}  // namespace lunetix