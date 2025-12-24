#include "lunetix/browser/lunetix_content_browser_client.h"

#include "base/command_line.h"
#include "base/strings/string_util.h"
#include "chrome/browser/chrome_browser_main.h"
#include "chrome/common/chrome_version.h"
#include "content/public/common/user_agent.h"
#include "lunetix/browser/lunetix_browser_main_parts.h"
#include "lunetix/common/lunetix_constants.h"

namespace lunetix {

LunetixContentBrowserClient::LunetixContentBrowserClient() = default;

LunetixContentBrowserClient::~LunetixContentBrowserClient() = default;

std::unique_ptr<content::BrowserMainParts>
LunetixContentBrowserClient::CreateBrowserMainParts(bool is_integration_test) {
  std::unique_ptr<LunetixBrowserMainParts> main_parts =
      std::make_unique<LunetixBrowserMainParts>(is_integration_test);
  return std::move(main_parts);
}

std::string LunetixContentBrowserClient::GetApplicationName() {
  return kLunetixApplicationName;
}

std::string LunetixContentBrowserClient::GetUserAgent() {
  std::string user_agent = content::BuildUserAgentFromProduct(
      kLunetixProductName "/" CHROME_VERSION_STRING);
  return user_agent;
}

std::u16string LunetixContentBrowserClient::GetApplicationNameForProtocolHandler() {
  return base::ASCIIToUTF16(kLunetixApplicationName);
}

void LunetixContentBrowserClient::AppendExtraCommandLineSwitches(
    base::CommandLine* command_line,
    int child_process_id) {
  ChromeContentBrowserClient::AppendExtraCommandLineSwitches(command_line,
                                                              child_process_id);
}

}  // namespace lunetix