#include "lunetix/browser/ui/lunetix_browser_window.h"

#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_window_state.h"

namespace lunetix {

LunetixBrowserWindow::LunetixBrowserWindow() = default;

LunetixBrowserWindow::~LunetixBrowserWindow() = default;

void LunetixBrowserWindow::Show() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::ShowInactive() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::Hide() {
  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::IsVisible() const {
  return false;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::SetBounds(const gfx::Rect& bounds) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::Close() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::Activate() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::Deactivate() {
  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::IsActive() const {
  return false;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::FlashFrame(bool flash) {
  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::IsAlwaysOnTop() const {
  return false;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::SetAlwaysOnTop(bool always_on_top) {
  // Implementation delegated to platform-specific code
}

gfx::NativeWindow LunetixBrowserWindow::GetNativeWindow() const {
  return nullptr;  // Implementation delegated to platform-specific code
}

StatusBubble* LunetixBrowserWindow::GetStatusBubble() {
  return nullptr;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::UpdateTitleBar() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::BookmarkBarStateChanged(
    BookmarkBar::AnimateChangeType change_type) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::UpdateDevTools() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::UpdateLoadingAnimations(bool should_animate) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::SetStarredState(bool is_starred) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::SetTranslateIconToggled(bool is_lit) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::OnActiveTabChanged(content::WebContents* old_contents,
                                             content::WebContents* new_contents,
                                             int index,
                                             int reason) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::ZoomChangedForActiveTab(bool can_show_bubble) {
  // Implementation delegated to platform-specific code
}

gfx::Rect LunetixBrowserWindow::GetRestoredBounds() const {
  return gfx::Rect();  // Implementation delegated to platform-specific code
}

ui::WindowShowState LunetixBrowserWindow::GetRestoredState() const {
  return ui::SHOW_STATE_NORMAL;  // Implementation delegated to platform-specific code
}

gfx::Rect LunetixBrowserWindow::GetBounds() const {
  return gfx::Rect();  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::IsMaximized() const {
  return false;  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::IsMinimized() const {
  return false;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::Maximize() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::Minimize() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::Restore() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::EnterFullscreen(const GURL& url,
                                          ExclusiveAccessBubbleType bubble_type,
                                          bool with_toolbar) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::ExitFullscreen() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::UpdateExclusiveAccessExitBubbleContent(
    const GURL& url,
    ExclusiveAccessBubbleType bubble_type,
    ExclusiveAccessBubbleHideCallback bubble_first_hide_callback,
    bool notify_download,
    bool force_update) {
  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::IsFullscreen() const {
  return false;  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::IsFullscreenBubbleVisible() const {
  return false;  // Implementation delegated to platform-specific code
}

LocationBar* LunetixBrowserWindow::GetLocationBar() const {
  return nullptr;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::SetFocusToLocationBar(bool select_all) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::UpdateReloadStopState(bool is_loading, bool force) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::UpdateToolbar(content::WebContents* contents) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::ResetToolbarTabState(content::WebContents* contents) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::FocusToolbar() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::FocusAppMenu() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::FocusBookmarksToolbar() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::FocusInfobars() {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::RotatePaneFocus(bool forwards) {
  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::ShowAppMenu() {
  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::PreHandleKeyboardEvent(
    const content::NativeWebKeyboardEvent& event,
    bool* is_keyboard_shortcut) {
  return false;  // Implementation delegated to platform-specific code
}

bool LunetixBrowserWindow::HandleKeyboardEvent(
    const content::NativeWebKeyboardEvent& event) {
  return false;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::CutCopyPaste(int command_id) {
  // Implementation delegated to platform-specific code
}

WindowOpenDisposition LunetixBrowserWindow::GetDispositionForPopupBounds(
    const gfx::Rect& bounds) {
  return WindowOpenDisposition::NEW_POPUP;
}

FindBar* LunetixBrowserWindow::CreateFindBar() {
  return nullptr;  // Implementation delegated to platform-specific code
}

web_modal::WebContentsModalDialogHost*
LunetixBrowserWindow::GetWebContentsModalDialogHost() {
  return nullptr;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::ShowAvatarBubbleFromAvatarButton(
    AvatarBubbleMode mode,
    const signin::ManageAccountsParams& manage_accounts_params,
    signin_metrics::AccessPoint access_point,
    bool is_source_keyboard) {
  // Implementation delegated to platform-specific code
}

int LunetixBrowserWindow::GetRenderViewHeightInsetWithDetachedBookmarkBar() {
  return 0;  // Implementation delegated to platform-specific code
}

void LunetixBrowserWindow::ExecuteExtensionCommand(
    const extensions::Extension* extension,
    const extensions::Command& command) {
  // Implementation delegated to platform-specific code
}

ExclusiveAccessContext* LunetixBrowserWindow::GetExclusiveAccessContext() {
  return nullptr;  // Implementation delegated to platform-specific code
}

}  // namespace lunetix