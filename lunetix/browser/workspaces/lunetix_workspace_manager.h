#ifndef LUNETIX_BROWSER_WORKSPACES_LUNETIX_WORKSPACE_MANAGER_H_
#define LUNETIX_BROWSER_WORKSPACES_LUNETIX_WORKSPACE_MANAGER_H_

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "content/public/browser/web_contents.h"

namespace lunetix {

class LunetixWorkspace {
 public:
  LunetixWorkspace(const std::string& id, const std::string& name);
  ~LunetixWorkspace();

  const std::string& id() const { return id_; }
  const std::string& name() const { return name_; }
  void set_name(const std::string& name) { name_ = name; }
  
  const std::string& color() const { return color_; }
  void set_color(const std::string& color) { color_ = color; }
  
  const std::vector<content::WebContents*>& tabs() const { return tabs_; }
  
  void AddTab(content::WebContents* web_contents);
  void RemoveTab(content::WebContents* web_contents);
  void MoveTab(content::WebContents* web_contents, int new_index);
  
  bool IsEmpty() const { return tabs_.empty(); }
  size_t GetTabCount() const { return tabs_.size(); }
  
  void SetActive(bool active) { is_active_ = active; }
  bool IsActive() const { return is_active_; }
  
 private:
  std::string id_;
  std::string name_;
  std::string color_;
  std::vector<content::WebContents*> tabs_;
  bool is_active_ = false;
  
  DISALLOW_COPY_AND_ASSIGN(LunetixWorkspace);
};

class LunetixWorkspaceManager : public TabStripModelObserver {
 public:
  class Observer {
   public:
    virtual ~Observer() = default;
    virtual void OnWorkspaceCreated(LunetixWorkspace* workspace) {}
    virtual void OnWorkspaceRemoved(const std::string& workspace_id) {}
    virtual void OnWorkspaceActivated(LunetixWorkspace* workspace) {}
    virtual void OnWorkspaceRenamed(LunetixWorkspace* workspace) {}
    virtual void OnTabMovedToWorkspace(content::WebContents* web_contents,
                                      LunetixWorkspace* workspace) {}
  };
  
  LunetixWorkspaceManager();
  ~LunetixWorkspaceManager() override;
  
  // Workspace management
  LunetixWorkspace* CreateWorkspace(const std::string& name);
  void RemoveWorkspace(const std::string& workspace_id);
  void RenameWorkspace(const std::string& workspace_id, const std::string& new_name);
  void SetWorkspaceColor(const std::string& workspace_id, const std::string& color);
  
  // Workspace navigation
  void ActivateWorkspace(const std::string& workspace_id);
  LunetixWorkspace* GetActiveWorkspace() const;
  LunetixWorkspace* GetWorkspace(const std::string& workspace_id) const;
  const std::vector<std::unique_ptr<LunetixWorkspace>>& GetAllWorkspaces() const;
  
  // Tab management
  void MoveTabToWorkspace(content::WebContents* web_contents, 
                         const std::string& workspace_id);
  void CreateTabGroup(const std::vector<content::WebContents*>& tabs,
                     const std::string& group_name,
                     const std::string& color);
  void UngroupTabs(const std::vector<content::WebContents*>& tabs);
  
  // Tab grouping
  struct TabGroup {
    std::string id;
    std::string name;
    std::string color;
    std::vector<content::WebContents*> tabs;
    bool collapsed = false;
  };
  
  TabGroup* CreateTabGroupInWorkspace(const std::string& workspace_id,
                                     const std::string& group_name,
                                     const std::string& color);
  void RemoveTabGroup(const std::string& group_id);
  void CollapseTabGroup(const std::string& group_id, bool collapsed);
  
  // Observer management
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);
  
  // TabStripModelObserver overrides:
  void OnTabStripModelChanged(TabStripModel* tab_strip_model,
                             const TabStripModelChange& change,
                             const TabStripSelectionChange& selection) override;
  
  // Persistence
  void SaveWorkspaces();
  void LoadWorkspaces();
  
 private:
  void NotifyWorkspaceCreated(LunetixWorkspace* workspace);
  void NotifyWorkspaceRemoved(const std::string& workspace_id);
  void NotifyWorkspaceActivated(LunetixWorkspace* workspace);
  
  std::string GenerateWorkspaceId();
  std::string GenerateGroupId();
  
  std::vector<std::unique_ptr<LunetixWorkspace>> workspaces_;
  std::map<std::string, std::unique_ptr<TabGroup>> tab_groups_;
  LunetixWorkspace* active_workspace_ = nullptr;
  
  base::ObserverList<Observer> observers_;
  
  int next_workspace_id_ = 1;
  int next_group_id_ = 1;
  
  base::WeakPtrFactory<LunetixWorkspaceManager> weak_factory_{this};
  
  DISALLOW_COPY_AND_ASSIGN(LunetixWorkspaceManager);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_WORKSPACES_LUNETIX_WORKSPACE_MANAGER_H_