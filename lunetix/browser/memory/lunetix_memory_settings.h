#ifndef LUNETIX_BROWSER_MEMORY_LUNETIX_MEMORY_SETTINGS_H_
#define LUNETIX_BROWSER_MEMORY_LUNETIX_MEMORY_SETTINGS_H_

#include "base/time/time.h"

namespace lunetix {

class LunetixMemorySettings {
 public:
  // Memory optimization preferences
  static const char kMemoryOptimizerEnabled[];
  static const char kTabSuspensionEnabled[];
  static const char kInactivityThresholdMinutes[];
  static const char kMemoryThresholdMB[];
  static const char kAggressiveMemoryMode[];
  static const char kSuspendBackgroundTabs[];
  static const char kPreventSuspensionOnMedia[];
  static const char kPreventSuspensionOnForms[];
  static const char kMemoryOptimizerNotifications[];
  
  // Default values
  static constexpr bool kDefaultMemoryOptimizerEnabled = true;
  static constexpr bool kDefaultTabSuspensionEnabled = true;
  static constexpr int kDefaultInactivityThresholdMinutes = 30;
  static constexpr int kDefaultMemoryThresholdMB = 2048;
  static constexpr bool kDefaultAggressiveMemoryMode = false;
  static constexpr bool kDefaultSuspendBackgroundTabs = true;
  static constexpr bool kDefaultPreventSuspensionOnMedia = true;
  static constexpr bool kDefaultPreventSuspensionOnForms = true;
  static constexpr bool kDefaultMemoryOptimizerNotifications = true;
  
  // Memory optimization levels
  enum class OptimizationLevel {
    DISABLED = 0,
    CONSERVATIVE = 1,
    BALANCED = 2,
    AGGRESSIVE = 3
  };
  
  static OptimizationLevel GetOptimizationLevel();
  static void SetOptimizationLevel(OptimizationLevel level);
  
  static base::TimeDelta GetInactivityThreshold();
  static void SetInactivityThreshold(base::TimeDelta threshold);
  
  static size_t GetMemoryThreshold();
  static void SetMemoryThreshold(size_t memory_mb);
  
 private:
  LunetixMemorySettings() = delete;
  ~LunetixMemorySettings() = delete;
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_MEMORY_LUNETIX_MEMORY_SETTINGS_H_