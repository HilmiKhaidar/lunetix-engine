#ifndef LUNETIX_BROWSER_LUNETIX_CONTENT_BROWSER_CLIENT_H_
#define LUNETIX_BROWSER_LUNETIX_CONTENT_BROWSER_CLIENT_H_

#include "chrome/browser/chrome_content_browser_client.h"

namespace lunetix {

class LunetixContentBrowserClient : public ChromeContentBrowserClient {
 public:
  LunetixContentBrowserClient();
  ~LunetixContentBrowserClient() override;

  // ChromeContentBrowserClient overrides:
  std::unique_ptr<content::BrowserMainParts> CreateBrowserMainParts(
      bool is_integration_test) override;
  
  std::string GetApplicationName() override;
  std::string GetUserAgent() override;
  std::u16string GetApplicationNameForProtocolHandler() override;
  
  void AppendExtraCommandLineSwitches(base::CommandLine* command_line,
                                      int child_process_id) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixContentBrowserClient);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_LUNETIX_CONTENT_BROWSER_CLIENT_H_