#ifndef LUNETIX_BROWSER_EXTENSIONS_LUNETIX_EXTENSION_SYSTEM_H_
#define LUNETIX_BROWSER_EXTENSIONS_LUNETIX_EXTENSION_SYSTEM_H_

#include "extensions/browser/extension_system.h"

namespace lunetix {

class LunetixExtensionSystem : public extensions::ExtensionSystem {
 public:
  explicit LunetixExtensionSystem(content::BrowserContext* browser_context);
  ~LunetixExtensionSystem() override;

  // ExtensionSystem overrides:
  void InitForRegularProfile(bool extensions_enabled) override;
  extensions::ExtensionService* extension_service() override;
  extensions::RuntimeData* runtime_data() override;
  extensions::ManagementPolicy* management_policy() override;
  extensions::ServiceWorkerManager* service_worker_manager() override;
  extensions::UserScriptManager* user_script_manager() override;
  extensions::StateStore* state_store() override;
  extensions::StateStore* rules_store() override;
  extensions::StateStore* dynamic_user_scripts_store() override;
  extensions::InfoMap* info_map() override;
  extensions::QuotaService* quota_service() override;
  extensions::AppSorting* app_sorting() override;
  void RegisterExtensionWithRequestContexts(
      const extensions::Extension* extension,
      base::OnceClosure callback) override;
  void UnregisterExtensionWithRequestContexts(
      const std::string& extension_id) override;

 private:
  void InitializeExtensionService();
  
  content::BrowserContext* browser_context_;
  std::unique_ptr<extensions::ExtensionService> extension_service_;
  std::unique_ptr<extensions::RuntimeData> runtime_data_;
  std::unique_ptr<extensions::ManagementPolicy> management_policy_;
  std::unique_ptr<extensions::ServiceWorkerManager> service_worker_manager_;
  std::unique_ptr<extensions::UserScriptManager> user_script_manager_;
  std::unique_ptr<extensions::StateStore> state_store_;
  std::unique_ptr<extensions::StateStore> rules_store_;
  std::unique_ptr<extensions::StateStore> dynamic_user_scripts_store_;
  std::unique_ptr<extensions::InfoMap> info_map_;
  std::unique_ptr<extensions::QuotaService> quota_service_;
  std::unique_ptr<extensions::AppSorting> app_sorting_;

  DISALLOW_COPY_AND_ASSIGN(LunetixExtensionSystem);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_EXTENSIONS_LUNETIX_EXTENSION_SYSTEM_H_