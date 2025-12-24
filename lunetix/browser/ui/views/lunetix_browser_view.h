#ifndef LUNETIX_BROWSER_UI_VIEWS_LUNETIX_BROWSER_VIEW_H_
#define LUNETIX_BROWSER_UI_VIEWS_LUNETIX_BROWSER_VIEW_H_

#include "chrome/browser/ui/views/frame/browser_view.h"

namespace lunetix {

class LunetixBrowserView : public BrowserView {
 public:
  explicit LunetixBrowserView(std::unique_ptr<Browser> browser);
  ~LunetixBrowserView() override;

  // BrowserView overrides:
  void InitViews() override;
  void LoadingAnimationCallback() override;
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;
  void UpdateToolbar(content::WebContents* contents) override;
  void UpdateUIForContents(content::WebContents* contents) override;
  void RevealTabStripIfNeeded() override;
  bool ShouldShowWindowIcon() const override;
  bool ShouldShowWindowTitle() const override;
  std::u16string GetWindowTitle() const override;
  bool ShouldShowAvatar() const override;
  void ShowUpdateChromeDialog() override;
  void ShowBookmarkBubble(const GURL& url, bool already_bookmarked) override;
  void ShowTranslateBubble(content::WebContents* contents,
                          translate::TranslateStep step,
                          const std::string& source_language,
                          const std::string& target_language,
                          translate::TranslateErrors::Type error_type,
                          bool is_user_gesture) override;

 protected:
  // BrowserView overrides:
  void Layout() override;
  void ViewHierarchyChanged(
      const views::ViewHierarchyChangedDetails& details) override;
  void ChildPreferredSizeChanged(views::View* child) override;
  void GetAccessibleNodeData(ui::AXNodeData* node_data) override;

 private:
  void InitLunetixSpecificViews();
  
  DISALLOW_COPY_AND_ASSIGN(LunetixBrowserView);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_UI_VIEWS_LUNETIX_BROWSER_VIEW_H_