#include "lunetix/browser/memory/lunetix_memory_optimizer.h"

#include "base/bind.h"
#include "base/logging.h"
#include "base/memory/memory_pressure_monitor.h"
#include "base/metrics/histogram_macros.h"
#include "base/system/sys_info.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/memory/memory_kills_monitor.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/render_process_host.h"
#include "content/public/browser/web_contents.h"

namespace lunetix {

LunetixMemoryOptimizer::LunetixMemoryOptimizer() = default;

LunetixMemoryOptimizer::~LunetixMemoryOptimizer() {
  Stop();
}

void LunetixMemoryOptimizer::Start() {
  TabManager::Start();
  
  // Start periodic check for suspendable tabs
  check_timer_.Start(FROM_HERE, base::Minutes(5),
                    base::BindRepeating(&LunetixMemoryOptimizer::CheckForSuspendableTabs,
                                       base::Unretained(this)));
  
  // Monitor existing tabs
  for (Browser* browser : *BrowserList::GetInstance()) {
    TabStripModel* tab_strip = browser->tab_strip_model();
    for (int i = 0; i < tab_strip->count(); ++i) {
      OnTabCreated(tab_strip->GetWebContentsAt(i));
    }
  }
  
  LOG(INFO) << "Lunetix Memory Optimizer started";
}

void LunetixMemoryOptimizer::Stop() {
  check_timer_.Stop();
  
  // Resume all suspended tabs
  for (auto& pair : tab_info_map_) {
    if (pair.second.is_suspended) {
      ResumeTabInternal(pair.first);
    }
  }
  
  tab_info_map_.clear();
  TabManager::Stop();
  
  LOG(INFO) << "Lunetix Memory Optimizer stopped";
}

void LunetixMemoryOptimizer::SuspendInactiveTab(content::WebContents* web_contents) {
  if (!tab_suspension_enabled_ || !web_contents) {
    return;
  }
  
  auto it = tab_info_map_.find(web_contents);
  if (it == tab_info_map_.end() || it->second.is_suspended) {
    return;
  }
  
  SuspendTabInternal(web_contents);
}

void LunetixMemoryOptimizer::ResumeTab(content::WebContents* web_contents) {
  if (!web_contents) {
    return;
  }
  
  auto it = tab_info_map_.find(web_contents);
  if (it == tab_info_map_.end() || !it->second.is_suspended) {
    return;
  }
  
  ResumeTabInternal(web_contents);
}

bool LunetixMemoryOptimizer::IsTabSuspended(content::WebContents* web_contents) const {
  auto it = tab_info_map_.find(web_contents);
  return it != tab_info_map_.end() && it->second.is_suspended;
}

void LunetixMemoryOptimizer::SetTabSuspensionEnabled(bool enabled) {
  tab_suspension_enabled_ = enabled;
  
  if (!enabled) {
    // Resume all suspended tabs
    for (auto& pair : tab_info_map_) {
      if (pair.second.is_suspended) {
        ResumeTabInternal(pair.first);
      }
    }
  }
}

void LunetixMemoryOptimizer::SetInactivityThreshold(base::TimeDelta threshold) {
  inactivity_threshold_ = threshold;
}

void LunetixMemoryOptimizer::SetMemoryThreshold(size_t memory_mb) {
  memory_threshold_mb_ = memory_mb;
}

size_t LunetixMemoryOptimizer::GetSuspendedTabCount() const {
  size_t count = 0;
  for (const auto& pair : tab_info_map_) {
    if (pair.second.is_suspended) {
      count++;
    }
  }
  return count;
}

size_t LunetixMemoryOptimizer::GetMemorySavedMB() const {
  return total_memory_saved_mb_;
}

void LunetixMemoryOptimizer::OnTabCreated(content::WebContents* web_contents) {
  if (!web_contents) {
    return;
  }
  
  TabInfo info;
  info.last_active_time = base::TimeTicks::Now();
  info.web_contents = web_contents->GetWeakPtr();
  tab_info_map_[web_contents] = info;
  
  // Create observer for this tab
  new TabSuspensionObserver(web_contents, this);
}

void LunetixMemoryOptimizer::OnTabDestroyed(content::WebContents* web_contents) {
  tab_info_map_.erase(web_contents);
}

void LunetixMemoryOptimizer::OnTabActivated(content::WebContents* web_contents) {
  auto it = tab_info_map_.find(web_contents);
  if (it != tab_info_map_.end()) {
    it->second.last_active_time = base::TimeTicks::Now();
    
    // Resume tab if it was suspended
    if (it->second.is_suspended) {
      ResumeTabInternal(web_contents);
    }
  }
}

void LunetixMemoryOptimizer::OnTabDeactivated(content::WebContents* web_contents) {
  auto it = tab_info_map_.find(web_contents);
  if (it != tab_info_map_.end()) {
    it->second.last_active_time = base::TimeTicks::Now();
  }
}

void LunetixMemoryOptimizer::CheckForSuspendableTabs() {
  if (!tab_suspension_enabled_) {
    return;
  }
  
  CheckMemoryPressure();
  
  base::TimeTicks now = base::TimeTicks::Now();
  
  for (auto& pair : tab_info_map_) {
    content::WebContents* web_contents = pair.first;
    TabInfo& info = pair.second;
    
    if (!info.is_suspended && ShouldSuspendTab(info)) {
      SuspendTabInternal(web_contents);
    }
  }
}

void LunetixMemoryOptimizer::CheckMemoryPressure() {
  size_t total_memory_mb = base::SysInfo::AmountOfPhysicalMemoryMB();
  size_t available_memory_mb = base::SysInfo::AmountOfAvailablePhysicalMemoryMB();
  
  // If memory usage is high, be more aggressive with suspension
  if (available_memory_mb < (total_memory_mb * 0.2)) {  // Less than 20% available
    // Reduce inactivity threshold temporarily
    base::TimeDelta aggressive_threshold = base::Minutes(10);
    
    for (auto& pair : tab_info_map_) {
      TabInfo& info = pair.second;
      if (!info.is_suspended && 
          (base::TimeTicks::Now() - info.last_active_time) > aggressive_threshold) {
        SuspendTabInternal(pair.first);
      }
    }
  }
}

bool LunetixMemoryOptimizer::ShouldSuspendTab(const TabInfo& tab_info) const {
  if (tab_info.is_suspended || !tab_info.web_contents) {
    return false;
  }
  
  content::WebContents* web_contents = tab_info.web_contents.get();
  
  // Don't suspend active tab
  if (web_contents->GetVisibility() == content::Visibility::VISIBLE) {
    return false;
  }
  
  // Don't suspend tabs with active media
  if (web_contents->IsCurrentlyAudible() || web_contents->IsBeingCaptured()) {
    return false;
  }
  
  // Don't suspend tabs with form data
  if (web_contents->GetController().GetPendingEntry()) {
    return false;
  }
  
  // Check inactivity threshold
  base::TimeTicks now = base::TimeTicks::Now();
  if ((now - tab_info.last_active_time) < inactivity_threshold_) {
    return false;
  }
  
  return true;
}

size_t LunetixMemoryOptimizer::GetTabMemoryUsage(content::WebContents* web_contents) const {
  if (!web_contents) {
    return 0;
  }
  
  content::RenderProcessHost* process = web_contents->GetMainFrame()->GetProcess();
  if (!process) {
    return 0;
  }
  
  // Estimate memory usage (simplified)
  return process->GetResidentSetSize() / (1024 * 1024);  // Convert to MB
}

void LunetixMemoryOptimizer::SuspendTabInternal(content::WebContents* web_contents) {
  auto it = tab_info_map_.find(web_contents);
  if (it == tab_info_map_.end() || it->second.is_suspended) {
    return;
  }
  
  TabInfo& info = it->second;
  
  // Record memory usage before suspension
  info.memory_usage_before_suspend = GetTabMemoryUsage(web_contents);
  
  // Suspend the tab by discarding it
  web_contents->SetAudioMuted(true);
  web_contents->WasHidden();
  
  // Mark as suspended
  info.is_suspended = true;
  total_memory_saved_mb_ += info.memory_usage_before_suspend;
  
  LOG(INFO) << "Suspended tab: " << web_contents->GetVisibleURL().spec()
            << " (saved ~" << info.memory_usage_before_suspend << "MB)";
  
  UMA_HISTOGRAM_MEMORY_MB("Lunetix.MemoryOptimizer.TabSuspended.MemorySaved",
                          info.memory_usage_before_suspend);
}

void LunetixMemoryOptimizer::ResumeTabInternal(content::WebContents* web_contents) {
  auto it = tab_info_map_.find(web_contents);
  if (it == tab_info_map_.end() || !it->second.is_suspended) {
    return;
  }
  
  TabInfo& info = it->second;
  
  // Resume the tab
  web_contents->SetAudioMuted(false);
  web_contents->WasShown();
  
  // Update statistics
  total_memory_saved_mb_ -= info.memory_usage_before_suspend;
  
  // Mark as resumed
  info.is_suspended = false;
  info.last_active_time = base::TimeTicks::Now();
  info.memory_usage_before_suspend = 0;
  
  LOG(INFO) << "Resumed tab: " << web_contents->GetVisibleURL().spec();
  
  UMA_HISTOGRAM_TIMES("Lunetix.MemoryOptimizer.TabResumed.SuspensionDuration",
                      base::TimeTicks::Now() - info.last_active_time);
}

// TabSuspensionObserver implementation

TabSuspensionObserver::TabSuspensionObserver(content::WebContents* web_contents,
                                           LunetixMemoryOptimizer* optimizer)
    : content::WebContentsObserver(web_contents), optimizer_(optimizer) {}

TabSuspensionObserver::~TabSuspensionObserver() = default;

void TabSuspensionObserver::WebContentsDestroyed() {
  optimizer_->OnTabDestroyed(web_contents());
  delete this;
}

void TabSuspensionObserver::DidStartNavigation(content::NavigationHandle* navigation_handle) {
  if (navigation_handle->IsInMainFrame()) {
    optimizer_->OnTabActivated(web_contents());
  }
}

void TabSuspensionObserver::DidFinishNavigation(content::NavigationHandle* navigation_handle) {
  if (navigation_handle->IsInMainFrame() && navigation_handle->HasCommitted()) {
    optimizer_->OnTabActivated(web_contents());
  }
}

void TabSuspensionObserver::OnVisibilityChanged(content::Visibility visibility) {
  if (visibility == content::Visibility::VISIBLE) {
    optimizer_->OnTabActivated(web_contents());
  } else {
    optimizer_->OnTabDeactivated(web_contents());
  }
}

}  // namespace lunetix