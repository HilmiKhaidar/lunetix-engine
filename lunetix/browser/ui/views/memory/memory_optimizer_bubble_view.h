#ifndef LUNETIX_BROWSER_UI_VIEWS_MEMORY_MEMORY_OPTIMIZER_BUBBLE_VIEW_H_
#define LUNETIX_BROWSER_UI_VIEWS_MEMORY_MEMORY_OPTIMIZER_BUBBLE_VIEW_H_

#include "chrome/browser/ui/views/location_bar/location_bar_bubble_delegate_view.h"
#include "ui/views/controls/button/button.h"

namespace views {
class Label;
class ToggleButton;
class Slider;
}

namespace lunetix {

class LunetixMemoryOptimizer;

class MemoryOptimizerBubbleView : public LocationBarBubbleDelegateView {
 public:
  explicit MemoryOptimizerBubbleView(views::View* anchor_view,
                                    content::WebContents* web_contents,
                                    LunetixMemoryOptimizer* optimizer);
  ~MemoryOptimizerBubbleView() override;

  // LocationBarBubbleDelegateView overrides:
  void Init() override;
  std::u16string GetWindowTitle() const override;
  bool ShouldShowCloseButton() const override;
  void WindowClosing() override;

 private:
  void CreateControls();
  void UpdateMemoryStats();
  void OnToggleMemoryOptimizer();
  void OnInactivityThresholdChanged();
  void OnOptimizationLevelChanged();
  void OnSuspendAllTabs();
  void OnResumeAllTabs();
  
  // UI components
  views::Label* memory_stats_label_ = nullptr;
  views::Label* suspended_tabs_label_ = nullptr;
  views::ToggleButton* enable_toggle_ = nullptr;
  views::Slider* threshold_slider_ = nullptr;
  views::Button* suspend_all_button_ = nullptr;
  views::Button* resume_all_button_ = nullptr;
  views::Button* settings_button_ = nullptr;
  
  LunetixMemoryOptimizer* memory_optimizer_;
  
  base::WeakPtrFactory<MemoryOptimizerBubbleView> weak_factory_{this};
  
  DISALLOW_COPY_AND_ASSIGN(MemoryOptimizerBubbleView);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_UI_VIEWS_MEMORY_MEMORY_OPTIMIZER_BUBBLE_VIEW_H_