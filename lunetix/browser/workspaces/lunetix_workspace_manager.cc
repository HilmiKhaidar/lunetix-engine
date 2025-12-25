#include "lunetix/browser/workspaces/lunetix_workspace_manager.h"

#include "base/guid.h"
#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "base/strings/string_number_conversions.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_list.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "components/prefs/pref_service.h"

namespace lunetix {

// LunetixWorkspace implementation

LunetixWorkspace::LunetixWorkspace(const std::string& id, const std::string& name)
    : id_(id), name_(name), color_("#4285F4") {}

LunetixWorkspace::~LunetixWorkspace() = default;

void LunetixWorkspace::AddTab(content::WebContents* web_contents) {
  if (std::find(tabs_.begin(), tabs_.end(), web_contents) == tabs_.end()) {
    tabs_.push_back(web_contents);
  }
}

void LunetixWorkspace::RemoveTab(content::WebContents* web_contents) {
  auto it = std::find(tabs_.begin(), tabs_.end(), web_contents);
  if (it != tabs_.end()) {
    tabs_.erase(it);
  }
}

void LunetixWorkspace::MoveTab(content::WebContents* web_contents, int new_index) {
  RemoveTab(web_contents);
  if (new_index >= 0 && new_index <= static_cast<int>(tabs_.size())) {
    tabs_.insert(tabs_.begin() + new_index, web_contents);
  } else {
    tabs_.push_back(web_contents);
  }
}

// LunetixWorkspaceManager implementation

LunetixWorkspaceManager::LunetixWorkspaceManager() {
  // Create default workspace
  auto default_workspace = std::make_unique<LunetixWorkspace>("default", "Main");
  active_workspace_ = default_workspace.get();
  workspaces_.push_back(std::move(default_workspace));
  
  LoadWorkspaces();
}

LunetixWorkspaceManager::~LunetixWorkspaceManager() {
  SaveWorkspaces();
}

LunetixWorkspace* LunetixWorkspaceManager::CreateWorkspace(const std::string& name) {
  std::string id = GenerateWorkspaceId();
  auto workspace = std::make_unique<LunetixWorkspace>(id, name);
  LunetixWorkspace* workspace_ptr = workspace.get();
  
  workspaces_.push_back(std::move(workspace));
  
  NotifyWorkspaceCreated(workspace_ptr);
  SaveWorkspaces();
  
  return workspace_ptr;
}

void LunetixWorkspaceManager::RemoveWorkspace(const std::string& workspace_id) {
  if (workspace_id == "default") {
    return;  // Cannot remove default workspace
  }
  
  auto it = std::find_if(workspaces_.begin(), workspaces_.end(),
                        [&workspace_id](const std::unique_ptr<LunetixWorkspace>& ws) {
                          return ws->id() == workspace_id;
                        });
  
  if (it != workspaces_.end()) {
    LunetixWorkspace* workspace = it->get();
    
    // Move all tabs to default workspace
    if (!workspace->tabs().empty()) {
      LunetixWorkspace* default_workspace = GetWorkspace("default");
      for (content::WebContents* tab : workspace->tabs()) {
        default_workspace->AddTab(tab);
      }
    }
    
    // If this was the active workspace, switch to default
    if (active_workspace_ == workspace) {
      ActivateWorkspace("default");
    }
    
    workspaces_.erase(it);
    NotifyWorkspaceRemoved(workspace_id);
    SaveWorkspaces();
  }
}

void LunetixWorkspaceManager::RenameWorkspace(const std::string& workspace_id,
                                             const std::string& new_name) {
  LunetixWorkspace* workspace = GetWorkspace(workspace_id);
  if (workspace) {
    workspace->set_name(new_name);
    NotifyWorkspaceActivated(workspace);  // Trigger UI update
    SaveWorkspaces();
  }
}

void LunetixWorkspaceManager::SetWorkspaceColor(const std::string& workspace_id,
                                               const std::string& color) {
  LunetixWorkspace* workspace = GetWorkspace(workspace_id);
  if (workspace) {
    workspace->set_color(color);
    SaveWorkspaces();
  }
}

void LunetixWorkspaceManager::ActivateWorkspace(const std::string& workspace_id) {
  LunetixWorkspace* workspace = GetWorkspace(workspace_id);
  if (workspace && workspace != active_workspace_) {
    if (active_workspace_) {
      active_workspace_->SetActive(false);
    }
    
    active_workspace_ = workspace;
    workspace->SetActive(true);
    
    NotifyWorkspaceActivated(workspace);
  }
}

LunetixWorkspace* LunetixWorkspaceManager::GetActiveWorkspace() const {
  return active_workspace_;
}

LunetixWorkspace* LunetixWorkspaceManager::GetWorkspace(const std::string& workspace_id) const {
  auto it = std::find_if(workspaces_.begin(), workspaces_.end(),
                        [&workspace_id](const std::unique_ptr<LunetixWorkspace>& ws) {
                          return ws->id() == workspace_id;
                        });
  return it != workspaces_.end() ? it->get() : nullptr;
}

const std::vector<std::unique_ptr<LunetixWorkspace>>& 
LunetixWorkspaceManager::GetAllWorkspaces() const {
  return workspaces_;
}

void LunetixWorkspaceManager::MoveTabToWorkspace(content::WebContents* web_contents,
                                                const std::string& workspace_id) {
  LunetixWorkspace* target_workspace = GetWorkspace(workspace_id);
  if (!target_workspace) {
    return;
  }
  
  // Remove from current workspace
  for (auto& workspace : workspaces_) {
    workspace->RemoveTab(web_contents);
  }
  
  // Add to target workspace
  target_workspace->AddTab(web_contents);
  
  for (Observer& observer : observers_) {
    observer.OnTabMovedToWorkspace(web_contents, target_workspace);
  }
  
  SaveWorkspaces();
}

void LunetixWorkspaceManager::CreateTabGroup(const std::vector<content::WebContents*>& tabs,
                                           const std::string& group_name,
                                           const std::string& color) {
  if (tabs.empty()) {
    return;
  }
  
  std::string group_id = GenerateGroupId();
  auto group = std::make_unique<TabGroup>();
  group->id = group_id;
  group->name = group_name;
  group->color = color;
  group->tabs = tabs;
  
  tab_groups_[group_id] = std::move(group);
  SaveWorkspaces();
}

LunetixWorkspaceManager::TabGroup* LunetixWorkspaceManager::CreateTabGroupInWorkspace(
    const std::string& workspace_id,
    const std::string& group_name,
    const std::string& color) {
  
  std::string group_id = GenerateGroupId();
  auto group = std::make_unique<TabGroup>();
  group->id = group_id;
  group->name = group_name;
  group->color = color;
  
  TabGroup* group_ptr = group.get();
  tab_groups_[group_id] = std::move(group);
  
  SaveWorkspaces();
  return group_ptr;
}

void LunetixWorkspaceManager::RemoveTabGroup(const std::string& group_id) {
  tab_groups_.erase(group_id);
  SaveWorkspaces();
}

void LunetixWorkspaceManager::CollapseTabGroup(const std::string& group_id, bool collapsed) {
  auto it = tab_groups_.find(group_id);
  if (it != tab_groups_.end()) {
    it->second->collapsed = collapsed;
  }
}

void LunetixWorkspaceManager::AddObserver(Observer* observer) {
  observers_.AddObserver(observer);
}

void LunetixWorkspaceManager::RemoveObserver(Observer* observer) {
  observers_.RemoveObserver(observer);
}

void LunetixWorkspaceManager::OnTabStripModelChanged(
    TabStripModel* tab_strip_model,
    const TabStripModelChange& change,
    const TabStripSelectionChange& selection) {
  
  // Handle tab changes and update workspace accordingly
  if (change.type() == TabStripModelChange::kInserted) {
    for (const auto& contents : change.GetInsert()->contents) {
      if (active_workspace_) {
        active_workspace_->AddTab(contents.contents);
      }
    }
  } else if (change.type() == TabStripModelChange::kRemoved) {
    for (const auto& contents : change.GetRemove()->contents) {
      for (auto& workspace : workspaces_) {
        workspace->RemoveTab(contents.contents);
      }
    }
  }
  
  SaveWorkspaces();
}

void LunetixWorkspaceManager::SaveWorkspaces() {
  // Implementation would save workspace state to preferences
  // This is a simplified version
}

void LunetixWorkspaceManager::LoadWorkspaces() {
  // Implementation would load workspace state from preferences
  // This is a simplified version
}

void LunetixWorkspaceManager::NotifyWorkspaceCreated(LunetixWorkspace* workspace) {
  for (Observer& observer : observers_) {
    observer.OnWorkspaceCreated(workspace);
  }
}

void LunetixWorkspaceManager::NotifyWorkspaceRemoved(const std::string& workspace_id) {
  for (Observer& observer : observers_) {
    observer.OnWorkspaceRemoved(workspace_id);
  }
}

void LunetixWorkspaceManager::NotifyWorkspaceActivated(LunetixWorkspace* workspace) {
  for (Observer& observer : observers_) {
    observer.OnWorkspaceActivated(workspace);
  }
}

std::string LunetixWorkspaceManager::GenerateWorkspaceId() {
  return "workspace_" + base::NumberToString(next_workspace_id_++);
}

std::string LunetixWorkspaceManager::GenerateGroupId() {
  return "group_" + base::NumberToString(next_group_id_++);
}

}  // namespace lunetix