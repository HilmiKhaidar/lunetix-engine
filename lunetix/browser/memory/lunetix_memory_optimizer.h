#ifndef LUNETIX_BROWSER_MEMORY_LUNETIX_MEMORY_OPTIMIZER_H_
#define LUNETIX_BROWSER_MEMORY_LUNETIX_MEMORY_OPTIMIZER_H_

#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "chrome/browser/resource_coordinator/tab_manager.h"
#include "content/public/browser/web_contents_observer.h"

namespace content {
class WebContents;
}

namespace lunetix {

class LunetixMemoryOptimizer : public resource_coordinator::TabManager {
 public:
  LunetixMemoryOptimizer();
  ~LunetixMemoryOptimizer() override;

  // TabManager overrides:
  void Start() override;
  void Stop() override;
  
  // Memory optimization methods
  void SuspendInactiveTab(content::WebContents* web_contents);
  void ResumeTab(content::WebContents* web_contents);
  bool IsTabSuspended(content::WebContents* web_contents) const;
  void SetTabSuspensionEnabled(bool enabled);
  void SetInactivityThreshold(base::TimeDelta threshold);
  void SetMemoryThreshold(size_t memory_mb);
  
  // Statistics
  size_t GetSuspendedTabCount() const;
  size_t GetMemorySavedMB() const;
  
 private:
  struct TabInfo {
    base::TimeTicks last_active_time;
    bool is_suspended = false;
    size_t memory_usage_before_suspend = 0;
    base::WeakPtr<content::WebContents> web_contents;
  };
  
  void OnTabCreated(content::WebContents* web_contents);
  void OnTabDestroyed(content::WebContents* web_contents);
  void OnTabActivated(content::WebContents* web_contents);
  void OnTabDeactivated(content::WebContents* web_contents);
  
  void CheckForSuspendableTabs();
  void CheckMemoryPressure();
  bool ShouldSuspendTab(const TabInfo& tab_info) const;
  size_t GetTabMemoryUsage(content::WebContents* web_contents) const;
  
  void SuspendTabInternal(content::WebContents* web_contents);
  void ResumeTabInternal(content::WebContents* web_contents);
  
  // Configuration
  bool tab_suspension_enabled_ = true;
  base::TimeDelta inactivity_threshold_ = base::Minutes(30);
  size_t memory_threshold_mb_ = 2048;  // 2GB
  
  // State tracking
  std::map<content::WebContents*, TabInfo> tab_info_map_;
  base::RepeatingTimer check_timer_;
  
  // Statistics
  size_t total_memory_saved_mb_ = 0;
  
  base::WeakPtrFactory<LunetixMemoryOptimizer> weak_factory_{this};
  
  DISALLOW_COPY_AND_ASSIGN(LunetixMemoryOptimizer);
};

class TabSuspensionObserver : public content::WebContentsObserver {
 public:
  explicit TabSuspensionObserver(content::WebContents* web_contents,
                                LunetixMemoryOptimizer* optimizer);
  ~TabSuspensionObserver() override;
  
  // WebContentsObserver overrides:
  void WebContentsDestroyed() override;
  void DidStartNavigation(content::NavigationHandle* navigation_handle) override;
  void DidFinishNavigation(content::NavigationHandle* navigation_handle) override;
  void OnVisibilityChanged(content::Visibility visibility) override;
  
 private:
  LunetixMemoryOptimizer* optimizer_;
  
  DISALLOW_COPY_AND_ASSIGN(TabSuspensionObserver);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_MEMORY_LUNETIX_MEMORY_OPTIMIZER_H_