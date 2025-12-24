#include "lunetix/browser/memory/lunetix_memory_settings.h"

#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_manager.h"
#include "components/prefs/pref_service.h"

namespace lunetix {

// Preference keys
const char LunetixMemorySettings::kMemoryOptimizerEnabled[] = 
    "lunetix.memory.optimizer_enabled";
const char LunetixMemorySettings::kTabSuspensionEnabled[] = 
    "lunetix.memory.tab_suspension_enabled";
const char LunetixMemorySettings::kInactivityThresholdMinutes[] = 
    "lunetix.memory.inactivity_threshold_minutes";
const char LunetixMemorySettings::kMemoryThresholdMB[] = 
    "lunetix.memory.memory_threshold_mb";
const char LunetixMemorySettings::kAggressiveMemoryMode[] = 
    "lunetix.memory.aggressive_mode";
const char LunetixMemorySettings::kSuspendBackgroundTabs[] = 
    "lunetix.memory.suspend_background_tabs";
const char LunetixMemorySettings::kPreventSuspensionOnMedia[] = 
    "lunetix.memory.prevent_suspension_on_media";
const char LunetixMemorySettings::kPreventSuspensionOnForms[] = 
    "lunetix.memory.prevent_suspension_on_forms";
const char LunetixMemorySettings::kMemoryOptimizerNotifications[] = 
    "lunetix.memory.optimizer_notifications";

LunetixMemorySettings::OptimizationLevel 
LunetixMemorySettings::GetOptimizationLevel() {
  Profile* profile = ProfileManager::GetActiveUserProfile();
  if (!profile) {
    return OptimizationLevel::BALANCED;
  }
  
  PrefService* prefs = profile->GetPrefs();
  
  if (!prefs->GetBoolean(kMemoryOptimizerEnabled)) {
    return OptimizationLevel::DISABLED;
  }
  
  if (prefs->GetBoolean(kAggressiveMemoryMode)) {
    return OptimizationLevel::AGGRESSIVE;
  }
  
  int threshold_minutes = prefs->GetInteger(kInactivityThresholdMinutes);
  if (threshold_minutes <= 15) {
    return OptimizationLevel::AGGRESSIVE;
  } else if (threshold_minutes <= 30) {
    return OptimizationLevel::BALANCED;
  } else {
    return OptimizationLevel::CONSERVATIVE;
  }
}

void LunetixMemorySettings::SetOptimizationLevel(OptimizationLevel level) {
  Profile* profile = ProfileManager::GetActiveUserProfile();
  if (!profile) {
    return;
  }
  
  PrefService* prefs = profile->GetPrefs();
  
  switch (level) {
    case OptimizationLevel::DISABLED:
      prefs->SetBoolean(kMemoryOptimizerEnabled, false);
      break;
      
    case OptimizationLevel::CONSERVATIVE:
      prefs->SetBoolean(kMemoryOptimizerEnabled, true);
      prefs->SetBoolean(kAggressiveMemoryMode, false);
      prefs->SetInteger(kInactivityThresholdMinutes, 60);
      prefs->SetInteger(kMemoryThresholdMB, 4096);
      break;
      
    case OptimizationLevel::BALANCED:
      prefs->SetBoolean(kMemoryOptimizerEnabled, true);
      prefs->SetBoolean(kAggressiveMemoryMode, false);
      prefs->SetInteger(kInactivityThresholdMinutes, 30);
      prefs->SetInteger(kMemoryThresholdMB, 2048);
      break;
      
    case OptimizationLevel::AGGRESSIVE:
      prefs->SetBoolean(kMemoryOptimizerEnabled, true);
      prefs->SetBoolean(kAggressiveMemoryMode, true);
      prefs->SetInteger(kInactivityThresholdMinutes, 10);
      prefs->SetInteger(kMemoryThresholdMB, 1024);
      break;
  }
}

base::TimeDelta LunetixMemorySettings::GetInactivityThreshold() {
  Profile* profile = ProfileManager::GetActiveUserProfile();
  if (!profile) {
    return base::Minutes(kDefaultInactivityThresholdMinutes);
  }
  
  PrefService* prefs = profile->GetPrefs();
  int minutes = prefs->GetInteger(kInactivityThresholdMinutes);
  return base::Minutes(minutes);
}

void LunetixMemorySettings::SetInactivityThreshold(base::TimeDelta threshold) {
  Profile* profile = ProfileManager::GetActiveUserProfile();
  if (!profile) {
    return;
  }
  
  PrefService* prefs = profile->GetPrefs();
  prefs->SetInteger(kInactivityThresholdMinutes, threshold.InMinutes());
}

size_t LunetixMemorySettings::GetMemoryThreshold() {
  Profile* profile = ProfileManager::GetActiveUserProfile();
  if (!profile) {
    return kDefaultMemoryThresholdMB;
  }
  
  PrefService* prefs = profile->GetPrefs();
  return prefs->GetInteger(kMemoryThresholdMB);
}

void LunetixMemorySettings::SetMemoryThreshold(size_t memory_mb) {
  Profile* profile = ProfileManager::GetActiveUserProfile();
  if (!profile) {
    return;
  }
  
  PrefService* prefs = profile->GetPrefs();
  prefs->SetInteger(kMemoryThresholdMB, static_cast<int>(memory_mb));
}

}  // namespace lunetix