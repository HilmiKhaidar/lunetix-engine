#include "lunetix/browser/ui/views/memory/memory_optimizer_bubble_view.h"

#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "chrome/grit/generated_resources.h"
#include "lunetix/browser/memory/lunetix_memory_optimizer.h"
#include "lunetix/browser/memory/lunetix_memory_settings.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/controls/button/md_text_button.h"
#include "ui/views/controls/button/toggle_button.h"
#include "ui/views/controls/label.h"
#include "ui/views/controls/slider.h"
#include "ui/views/layout/box_layout.h"
#include "ui/views/layout/grid_layout.h"

namespace lunetix {

MemoryOptimizerBubbleView::MemoryOptimizerBubbleView(
    views::View* anchor_view,
    content::WebContents* web_contents,
    LunetixMemoryOptimizer* optimizer)
    : LocationBarBubbleDelegateView(anchor_view, web_contents),
      memory_optimizer_(optimizer) {
  SetButtons(ui::DIALOG_BUTTON_NONE);
}

MemoryOptimizerBubbleView::~MemoryOptimizerBubbleView() = default;

void MemoryOptimizerBubbleView::Init() {
  CreateControls();
  UpdateMemoryStats();
}

std::u16string MemoryOptimizerBubbleView::GetWindowTitle() const {
  return u"Memory Optimizer";
}

bool MemoryOptimizerBubbleView::ShouldShowCloseButton() const {
  return true;
}

void MemoryOptimizerBubbleView::WindowClosing() {
  // Save any pending settings changes
}

void MemoryOptimizerBubbleView::CreateControls() {
  ChromeLayoutProvider* provider = ChromeLayoutProvider::Get();
  
  // Main layout
  SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kVertical,
      provider->GetInsetsMetric(views::INSETS_DIALOG),
      provider->GetDistanceMetric(views::DISTANCE_RELATED_CONTROL_VERTICAL)));
  
  // Memory statistics section
  memory_stats_label_ = AddChildView(std::make_unique<views::Label>());
  memory_stats_label_->SetMultiLine(true);
  memory_stats_label_->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  
  suspended_tabs_label_ = AddChildView(std::make_unique<views::Label>());
  suspended_tabs_label_->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  
  // Separator
  AddChildView(std::make_unique<views::Separator>());
  
  // Enable/disable toggle
  auto toggle_container = std::make_unique<views::View>();
  toggle_container->SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kHorizontal));
  
  auto toggle_label = std::make_unique<views::Label>(u"Enable Memory Optimizer");
  toggle_container->AddChildView(std::move(toggle_label));
  
  enable_toggle_ = toggle_container->AddChildView(
      std::make_unique<views::ToggleButton>(
          base::BindRepeating(&MemoryOptimizerBubbleView::OnToggleMemoryOptimizer,
                             base::Unretained(this))));
  
  AddChildView(std::move(toggle_container));
  
  // Inactivity threshold slider
  auto threshold_container = std::make_unique<views::View>();
  threshold_container->SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kVertical));
  
  auto threshold_label = std::make_unique<views::Label>(
      u"Suspend tabs after (minutes):");
  threshold_container->AddChildView(std::move(threshold_label));
  
  threshold_slider_ = threshold_container->AddChildView(
      std::make_unique<views::Slider>(
          base::BindRepeating(&MemoryOptimizerBubbleView::OnInactivityThresholdChanged,
                             base::Unretained(this))));
  threshold_slider_->SetMinimum(5);
  threshold_slider_->SetMaximum(120);
  threshold_slider_->SetValue(30);
  
  AddChildView(std::move(threshold_container));
  
  // Action buttons
  auto button_container = std::make_unique<views::View>();
  button_container->SetLayoutManager(std::make_unique<views::BoxLayout>(
      views::BoxLayout::Orientation::kHorizontal,
      gfx::Insets(),
      provider->GetDistanceMetric(views::DISTANCE_RELATED_BUTTON_HORIZONTAL)));
  
  suspend_all_button_ = button_container->AddChildView(
      std::make_unique<views::MdTextButton>(
          base::BindRepeating(&MemoryOptimizerBubbleView::OnSuspendAllTabs,
                             base::Unretained(this)),
          u"Suspend All"));
  
  resume_all_button_ = button_container->AddChildView(
      std::make_unique<views::MdTextButton>(
          base::BindRepeating(&MemoryOptimizerBubbleView::OnResumeAllTabs,
                             base::Unretained(this)),
          u"Resume All"));
  
  AddChildView(std::move(button_container));
  
  // Settings button
  settings_button_ = AddChildView(std::make_unique<views::MdTextButton>(
      base::BindRepeating(&MemoryOptimizerBubbleView::OnOptimizationLevelChanged,
                         base::Unretained(this)),
      u"Advanced Settings"));
}

void MemoryOptimizerBubbleView::UpdateMemoryStats() {
  if (!memory_optimizer_) {
    return;
  }
  
  size_t suspended_count = memory_optimizer_->GetSuspendedTabCount();
  size_t memory_saved_mb = memory_optimizer_->GetMemorySavedMB();
  
  std::u16string stats_text = base::ASCIIToUTF16(
      "Memory saved: " + base::NumberToString(memory_saved_mb) + " MB");
  memory_stats_label_->SetText(stats_text);
  
  std::u16string tabs_text = base::ASCIIToUTF16(
      "Suspended tabs: " + base::NumberToString(suspended_count));
  suspended_tabs_label_->SetText(tabs_text);
  
  // Update toggle state
  LunetixMemorySettings::OptimizationLevel level = 
      LunetixMemorySettings::GetOptimizationLevel();
  enable_toggle_->SetIsOn(level != LunetixMemorySettings::OptimizationLevel::DISABLED);
  
  // Update threshold slider
  base::TimeDelta threshold = LunetixMemorySettings::GetInactivityThreshold();
  threshold_slider_->SetValue(static_cast<float>(threshold.InMinutes()));
}

void MemoryOptimizerBubbleView::OnToggleMemoryOptimizer() {
  bool enabled = enable_toggle_->GetIsOn();
  
  if (enabled) {
    LunetixMemorySettings::SetOptimizationLevel(
        LunetixMemorySettings::OptimizationLevel::BALANCED);
  } else {
    LunetixMemorySettings::SetOptimizationLevel(
        LunetixMemorySettings::OptimizationLevel::DISABLED);
  }
  
  UpdateMemoryStats();
}

void MemoryOptimizerBubbleView::OnInactivityThresholdChanged() {
  int minutes = static_cast<int>(threshold_slider_->GetValue());
  LunetixMemorySettings::SetInactivityThreshold(base::Minutes(minutes));
}

void MemoryOptimizerBubbleView::OnOptimizationLevelChanged() {
  // Open advanced settings dialog
  // This would typically open a separate settings page
}

void MemoryOptimizerBubbleView::OnSuspendAllTabs() {
  // Suspend all eligible tabs immediately
  if (memory_optimizer_) {
    // Implementation would iterate through all tabs and suspend them
  }
  UpdateMemoryStats();
}

void MemoryOptimizerBubbleView::OnResumeAllTabs() {
  // Resume all suspended tabs
  if (memory_optimizer_) {
    // Implementation would iterate through all suspended tabs and resume them
  }
  UpdateMemoryStats();
}

}  // namespace lunetix