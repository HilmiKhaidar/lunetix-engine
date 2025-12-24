#ifndef LUNETIX_BROWSER_UI_LUNETIX_BROWSER_WINDOW_H_
#define LUNETIX_BROWSER_UI_LUNETIX_BROWSER_WINDOW_H_

#include "chrome/browser/ui/browser_window.h"

namespace lunetix {

class LunetixBrowserWindow : public BrowserWindow {
 public:
  LunetixBrowserWindow();
  ~LunetixBrowserWindow() override;

  // BrowserWindow overrides:
  void Show() override;
  void ShowInactive() override;
  void Hide() override;
  bool IsVisible() const override;
  void SetBounds(const gfx::Rect& bounds) override;
  void Close() override;
  void Activate() override;
  void Deactivate() override;
  bool IsActive() const override;
  void FlashFrame(bool flash) override;
  bool IsAlwaysOnTop() const override;
  void SetAlwaysOnTop(bool always_on_top) override;
  gfx::NativeWindow GetNativeWindow() const override;
  StatusBubble* GetStatusBubble() override;
  void UpdateTitleBar() override;
  void BookmarkBarStateChanged(
      BookmarkBar::AnimateChangeType change_type) override;
  void UpdateDevTools() override;
  void UpdateLoadingAnimations(bool should_animate) override;
  void SetStarredState(bool is_starred) override;
  void SetTranslateIconToggled(bool is_lit) override;
  void OnActiveTabChanged(content::WebContents* old_contents,
                         content::WebContents* new_contents,
                         int index,
                         int reason) override;
  void ZoomChangedForActiveTab(bool can_show_bubble) override;
  gfx::Rect GetRestoredBounds() const override;
  ui::WindowShowState GetRestoredState() const override;
  gfx::Rect GetBounds() const override;
  bool IsMaximized() const override;
  bool IsMinimized() const override;
  void Maximize() override;
  void Minimize() override;
  void Restore() override;
  void EnterFullscreen(const GURL& url,
                      ExclusiveAccessBubbleType bubble_type,
                      bool with_toolbar) override;
  void ExitFullscreen() override;
  void UpdateExclusiveAccessExitBubbleContent(
      const GURL& url,
      ExclusiveAccessBubbleType bubble_type,
      ExclusiveAccessBubbleHideCallback bubble_first_hide_callback,
      bool notify_download,
      bool force_update) override;
  bool IsFullscreen() const override;
  bool IsFullscreenBubbleVisible() const override;
  LocationBar* GetLocationBar() const override;
  void SetFocusToLocationBar(bool select_all) override;
  void UpdateReloadStopState(bool is_loading, bool force) override;
  void UpdateToolbar(content::WebContents* contents) override;
  void ResetToolbarTabState(content::WebContents* contents) override;
  void FocusToolbar() override;
  void FocusAppMenu() override;
  void FocusBookmarksToolbar() override;
  void FocusInfobars() override;
  void RotatePaneFocus(bool forwards) override;
  void ShowAppMenu() override;
  bool PreHandleKeyboardEvent(const content::NativeWebKeyboardEvent& event,
                             bool* is_keyboard_shortcut) override;
  bool HandleKeyboardEvent(
      const content::NativeWebKeyboardEvent& event) override;
  void CutCopyPaste(int command_id) override;
  WindowOpenDisposition GetDispositionForPopupBounds(
      const gfx::Rect& bounds) override;
  FindBar* CreateFindBar() override;
  web_modal::WebContentsModalDialogHost* GetWebContentsModalDialogHost()
      override;
  void ShowAvatarBubbleFromAvatarButton(
      AvatarBubbleMode mode,
      const signin::ManageAccountsParams& manage_accounts_params,
      signin_metrics::AccessPoint access_point,
      bool is_source_keyboard) override;
  int GetRenderViewHeightInsetWithDetachedBookmarkBar() override;
  void ExecuteExtensionCommand(const extensions::Extension* extension,
                              const extensions::Command& command) override;
  ExclusiveAccessContext* GetExclusiveAccessContext() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixBrowserWindow);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_UI_LUNETIX_BROWSER_WINDOW_H_