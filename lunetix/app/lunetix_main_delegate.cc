#include "lunetix/app/lunetix_main_delegate.h"

#include "base/command_line.h"
#include "base/path_service.h"
#include "chrome/browser/chrome_content_browser_client.h"
#include "chrome/common/chrome_paths.h"
#include "chrome/renderer/chrome_content_renderer_client.h"
#include "chrome/utility/chrome_content_utility_client.h"
#include "content/public/common/content_switches.h"
#include "lunetix/browser/lunetix_content_browser_client.h"
#include "lunetix/common/lunetix_paths.h"
#include "lunetix/renderer/lunetix_content_renderer_client.h"
#include "lunetix/utility/lunetix_content_utility_client.h"

namespace lunetix {

LunetixMainDelegate::LunetixMainDelegate(base::TimeTicks exe_entry_point_ticks)
    : ChromeMainDelegate(exe_entry_point_ticks),
      exe_entry_point_ticks_(exe_entry_point_ticks) {}

LunetixMainDelegate::~LunetixMainDelegate() = default;

std::optional<int> LunetixMainDelegate::BasicStartupComplete() {
  lunetix::RegisterPathProvider();
  return ChromeMainDelegate::BasicStartupComplete();
}

void LunetixMainDelegate::PreSandboxStartup() {
  ChromeMainDelegate::PreSandboxStartup();
}

std::optional<int> LunetixMainDelegate::PreBrowserMain() {
  return ChromeMainDelegate::PreBrowserMain();
}

std::optional<int> LunetixMainDelegate::PostEarlyInitialization(
    InvokedIn invoked_in) {
  return ChromeMainDelegate::PostEarlyInitialization(invoked_in);
}

content::ContentBrowserClient*
LunetixMainDelegate::CreateContentBrowserClient() {
  return new LunetixContentBrowserClient();
}

content::ContentRendererClient*
LunetixMainDelegate::CreateContentRendererClient() {
  return new LunetixContentRendererClient();
}

content::ContentUtilityClient*
LunetixMainDelegate::CreateContentUtilityClient() {
  return new LunetixContentUtilityClient();
}

}  // namespace lunetix