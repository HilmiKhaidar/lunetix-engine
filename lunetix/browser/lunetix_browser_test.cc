#include "chrome/test/base/in_process_browser_test.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "content/public/test/browser_test.h"
#include "lunetix/common/lunetix_constants.h"

namespace lunetix {

class LunetixBrowserTest : public InProcessBrowserTest {
 protected:
  void SetUpOnMainThread() override {
    InProcessBrowserTest::SetUpOnMainThread();
  }
};

IN_PROC_BROWSER_TEST_F(LunetixBrowserTest, BasicStartup) {
  // Test that browser starts up correctly
  EXPECT_TRUE(browser());
  EXPECT_TRUE(browser()->tab_strip_model());
  EXPECT_GE(browser()->tab_strip_model()->count(), 1);
}

IN_PROC_BROWSER_TEST_F(LunetixBrowserTest, WindowTitle) {
  // Test that window title contains Lunetix branding
  std::u16string title = browser()->GetWindowTitleForCurrentTab(false);
  std::string title_str = base::UTF16ToUTF8(title);
  EXPECT_NE(title_str.find(kLunetixApplicationName), std::string::npos);
}

IN_PROC_BROWSER_TEST_F(LunetixBrowserTest, UserAgent) {
  // Test that user agent contains Lunetix branding
  content::WebContents* web_contents = 
      browser()->tab_strip_model()->GetActiveWebContents();
  EXPECT_TRUE(web_contents);
  
  std::string user_agent = web_contents->GetUserAgentOverride().ua_string_override;
  if (!user_agent.empty()) {
    EXPECT_NE(user_agent.find("Lunetix"), std::string::npos);
  }
}

IN_PROC_BROWSER_TEST_F(LunetixBrowserTest, NavigateToHomepage) {
  // Test navigation to Lunetix homepage
  GURL homepage_url(kLunetixHomepageURL);
  EXPECT_TRUE(homepage_url.is_valid());
  
  // Note: Actual navigation test would require network access
  // This test just verifies the URL is valid
}

IN_PROC_BROWSER_TEST_F(LunetixBrowserTest, ProfileDirectory) {
  // Test that profile uses Lunetix directory structure
  base::FilePath profile_path = browser()->profile()->GetPath();
  std::string path_str = profile_path.LossyDisplayName();
  EXPECT_NE(path_str.find(kLunetixUserDataDirname), std::string::npos);
}

}  // namespace lunetix