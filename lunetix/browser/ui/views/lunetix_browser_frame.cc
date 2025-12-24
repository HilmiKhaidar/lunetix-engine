#include "lunetix/browser/ui/views/lunetix_browser_frame.h"

#include "chrome/browser/ui/views/frame/browser_view.h"
#include "lunetix/browser/ui/views/lunetix_browser_view.h"

namespace lunetix {

LunetixBrowserFrame::LunetixBrowserFrame(BrowserView* browser_view)
    : BrowserFrame(browser_view) {}

LunetixBrowserFrame::~LunetixBrowserFrame() = default;

void LunetixBrowserFrame::InitBrowserFrame() {
  BrowserFrame::InitBrowserFrame();
}

int LunetixBrowserFrame::GetMinimizeButtonOffset() const {
  return BrowserFrame::GetMinimizeButtonOffset();
}

gfx::Rect LunetixBrowserFrame::GetBoundsForTabStripRegion(
    const gfx::Size& tabstrip_minimum_size) const {
  return BrowserFrame::GetBoundsForTabStripRegion(tabstrip_minimum_size);
}

int LunetixBrowserFrame::GetTopInset(bool restored) const {
  return BrowserFrame::GetTopInset(restored);
}

int LunetixBrowserFrame::GetThemeBackgroundXInset() const {
  return BrowserFrame::GetThemeBackgroundXInset();
}

void LunetixBrowserFrame::UpdateThrobber(bool running) {
  BrowserFrame::UpdateThrobber(running);
}

views::View* LunetixBrowserFrame::GetFrameView() const {
  return BrowserFrame::GetFrameView();
}

void LunetixBrowserFrame::OnBoundsChanged(const gfx::Rect& previous_bounds) {
  BrowserFrame::OnBoundsChanged(previous_bounds);
}

}  // namespace lunetix