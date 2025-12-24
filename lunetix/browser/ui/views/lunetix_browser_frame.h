#ifndef LUNETIX_BROWSER_UI_VIEWS_LUNETIX_BROWSER_FRAME_H_
#define LUNETIX_BROWSER_UI_VIEWS_LUNETIX_BROWSER_FRAME_H_

#include "chrome/browser/ui/views/frame/browser_frame.h"

namespace lunetix {

class LunetixBrowserFrame : public BrowserFrame {
 public:
  explicit LunetixBrowserFrame(BrowserView* browser_view);
  ~LunetixBrowserFrame() override;

  // BrowserFrame overrides:
  void InitBrowserFrame() override;
  int GetMinimizeButtonOffset() const override;
  gfx::Rect GetBoundsForTabStripRegion(
      const gfx::Size& tabstrip_minimum_size) const override;
  int GetTopInset(bool restored) const override;
  int GetThemeBackgroundXInset() const override;
  void UpdateThrobber(bool running) override;
  views::View* GetFrameView() const override;

 protected:
  // BrowserFrame overrides:
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixBrowserFrame);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_UI_VIEWS_LUNETIX_BROWSER_FRAME_H_