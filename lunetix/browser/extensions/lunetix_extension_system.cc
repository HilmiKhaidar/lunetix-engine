#include "lunetix/browser/extensions/lunetix_extension_system.h"

#include "chrome/browser/extensions/chrome_app_sorting.h"
#include "chrome/browser/extensions/chrome_extension_web_contents_observer.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_system_provider.h"
#include "extensions/browser/info_map.h"
#include "extensions/browser/quota_service.h"
#include "extensions/browser/runtime_data.h"
#include "extensions/browser/service_worker_manager.h"
#include "extensions/browser/state_store.h"
#include "extensions/browser/user_script_manager.h"

namespace lunetix {

LunetixExtensionSystem::LunetixExtensionSystem(content::BrowserContext* browser_context)
    : browser_context_(browser_context) {}

LunetixExtensionSystem::~LunetixExtensionSystem() = default;

void LunetixExtensionSystem::InitForRegularProfile(bool extensions_enabled) {
  if (!extensions_enabled)
    return;

  InitializeExtensionService();
  
  runtime_data_ = std::make_unique<extensions::RuntimeData>(
      extensions::ExtensionRegistry::Get(browser_context_));
  
  management_policy_ = std::make_unique<extensions::ManagementPolicy>();
  
  service_worker_manager_ = std::make_unique<extensions::ServiceWorkerManager>(
      browser_context_);
  
  user_script_manager_ = std::make_unique<extensions::UserScriptManager>(
      browser_context_);
  
  state_store_ = std::make_unique<extensions::StateStore>(
      browser_context_, "Extension State", true);
  
  rules_store_ = std::make_unique<extensions::StateStore>(
      browser_context_, "Extension Rules", false);
  
  dynamic_user_scripts_store_ = std::make_unique<extensions::StateStore>(
      browser_context_, "Extension Dynamic User Scripts", false);
  
  info_map_ = std::make_unique<extensions::InfoMap>();
  
  quota_service_ = std::make_unique<extensions::QuotaService>();
  
  app_sorting_ = std::make_unique<extensions::ChromeAppSorting>(
      static_cast<Profile*>(browser_context_));
}

extensions::ExtensionService* LunetixExtensionSystem::extension_service() {
  return extension_service_.get();
}

extensions::RuntimeData* LunetixExtensionSystem::runtime_data() {
  return runtime_data_.get();
}

extensions::ManagementPolicy* LunetixExtensionSystem::management_policy() {
  return management_policy_.get();
}

extensions::ServiceWorkerManager* LunetixExtensionSystem::service_worker_manager() {
  return service_worker_manager_.get();
}

extensions::UserScriptManager* LunetixExtensionSystem::user_script_manager() {
  return user_script_manager_.get();
}

extensions::StateStore* LunetixExtensionSystem::state_store() {
  return state_store_.get();
}

extensions::StateStore* LunetixExtensionSystem::rules_store() {
  return rules_store_.get();
}

extensions::StateStore* LunetixExtensionSystem::dynamic_user_scripts_store() {
  return dynamic_user_scripts_store_.get();
}

extensions::InfoMap* LunetixExtensionSystem::info_map() {
  return info_map_.get();
}

extensions::QuotaService* LunetixExtensionSystem::quota_service() {
  return quota_service_.get();
}

extensions::AppSorting* LunetixExtensionSystem::app_sorting() {
  return app_sorting_.get();
}

void LunetixExtensionSystem::RegisterExtensionWithRequestContexts(
    const extensions::Extension* extension,
    base::OnceClosure callback) {
  if (info_map_) {
    info_map_->AddExtension(extension, base::Time::Now(), false, false);
  }
  std::move(callback).Run();
}

void LunetixExtensionSystem::UnregisterExtensionWithRequestContexts(
    const std::string& extension_id) {
  if (info_map_) {
    info_map_->RemoveExtension(extension_id, extensions::UnloadedExtensionReason::UNINSTALL);
  }
}

void LunetixExtensionSystem::InitializeExtensionService() {
  // Extension service initialization would be implemented here
  // This is a placeholder for the actual implementation
}

}  // namespace lunetix