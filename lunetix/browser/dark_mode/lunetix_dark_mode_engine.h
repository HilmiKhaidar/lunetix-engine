#ifndef LUNETIX_BROWSER_DARK_MODE_LUNETIX_DARK_MODE_ENGINE_H_
#define LUNETIX_BROWSER_DARK_MODE_LUNETIX_DARK_MODE_ENGINE_H_

#include "base/memory/weak_ptr.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class WebContents;
}

namespace lunetix {

class LunetixDarkModeEngine : public content::WebContentsObserver,
                             public content::WebContentsUserData<LunetixDarkModeEngine> {
 public:
  ~LunetixDarkModeEngine() override;

  // Dark mode control
  void EnableDarkMode();
  void DisableDarkMode();
  void ToggleDarkMode();
  bool IsDarkModeEnabled() const { return is_dark_mode_enabled_; }
  
  // Dark mode settings
  enum class DarkModeType {
    SIMPLE_INVERT,      // Simple color inversion
    SMART_INVERT,       // Smart inversion preserving images
    CSS_FILTER,         // CSS filter-based approach
    CUSTOM_CSS,         // Custom dark mode CSS injection
    AUTO_DETECT         // Auto-detect and apply best method
  };
  
  void SetDarkModeType(DarkModeType type);
  DarkModeType GetDarkModeType() const { return dark_mode_type_; }
  
  // Customization options
  void SetBrightness(double brightness);      // 0.0 - 2.0
  void SetContrast(double contrast);          // 0.0 - 2.0
  void SetSepia(double sepia);                // 0.0 - 1.0
  void SetHueRotate(int degrees);             // 0 - 360
  
  double GetBrightness() const { return brightness_; }
  double GetContrast() const { return contrast_; }
  double GetSepia() const { return sepia_; }
  int GetHueRotate() const { return hue_rotate_; }
  
  // Site-specific settings
  void SetSiteExemption(const std::string& domain, bool exempt);
  bool IsSiteExempt(const std::string& domain) const;
  void ClearSiteExemptions();
  
  // Image handling
  void SetPreserveImages(bool preserve);
  bool ShouldPreserveImages() const { return preserve_images_; }
  
  void SetPreserveVideos(bool preserve);
  bool ShouldPreserveVideos() const { return preserve_videos_; }
  
  // WebContentsObserver overrides:
  void DidFinishNavigation(content::NavigationHandle* navigation_handle) override;
  void DocumentOnLoadCompletedInMainFrame() override;
  void DidFinishLoad(content::RenderFrameHost* render_frame_host,
                    const GURL& validated_url) override;
  
 private:
  friend class content::WebContentsUserData<LunetixDarkModeEngine>;
  
  explicit LunetixDarkModeEngine(content::WebContents* web_contents);
  
  void ApplyDarkMode();
  void RemoveDarkMode();
  void InjectDarkModeCSS();
  void InjectDarkModeJS();
  
  std::string GenerateSimpleInvertCSS();
  std::string GenerateSmartInvertCSS();
  std::string GenerateCSSFilterCSS();
  std::string GenerateCustomDarkCSS();
  std::string GenerateDarkModeJS();
  
  bool ShouldApplyDarkMode();
  std::string GetCurrentDomain();
  
  // Settings
  bool is_dark_mode_enabled_ = false;
  DarkModeType dark_mode_type_ = DarkModeType::SMART_INVERT;
  
  // Filter settings
  double brightness_ = 0.9;
  double contrast_ = 1.1;
  double sepia_ = 0.0;
  int hue_rotate_ = 180;
  
  // Preservation settings
  bool preserve_images_ = true;
  bool preserve_videos_ = true;
  
  // Site exemptions
  std::set<std::string> exempt_domains_;
  
  WEB_CONTENTS_USER_DATA_KEY_DECL();
  
  base::WeakPtrFactory<LunetixDarkModeEngine> weak_factory_{this};
  
  DISALLOW_COPY_AND_ASSIGN(LunetixDarkModeEngine);
};

class LunetixDarkModeController {
 public:
  static LunetixDarkModeController* GetInstance();
  
  // Global dark mode settings
  void SetGlobalDarkModeEnabled(bool enabled);
  bool IsGlobalDarkModeEnabled() const { return global_dark_mode_enabled_; }
  
  void SetDefaultDarkModeType(LunetixDarkModeEngine::DarkModeType type);
  LunetixDarkModeEngine::DarkModeType GetDefaultDarkModeType() const;
  
  // Auto dark mode
  void SetAutoDarkModeEnabled(bool enabled);
  bool IsAutoDarkModeEnabled() const { return auto_dark_mode_enabled_; }
  
  void SetAutoDarkModeSchedule(int start_hour, int end_hour);
  void GetAutoDarkModeSchedule(int* start_hour, int* end_hour) const;
  
  // System integration
  void SetFollowSystemTheme(bool follow);
  bool ShouldFollowSystemTheme() const { return follow_system_theme_; }
  
  // Apply to all tabs
  void ApplyDarkModeToAllTabs();
  void RemoveDarkModeFromAllTabs();
  
  // Site management
  void AddGlobalSiteExemption(const std::string& domain);
  void RemoveGlobalSiteExemption(const std::string& domain);
  bool IsGloballyExempt(const std::string& domain) const;
  
  // Statistics
  int GetDarkModeEnabledTabsCount() const;
  
 private:
  LunetixDarkModeController();
  ~LunetixDarkModeController();
  
  void CheckSystemTheme();
  void UpdateAutoDarkMode();
  
  // Global settings
  bool global_dark_mode_enabled_ = false;
  LunetixDarkModeEngine::DarkModeType default_dark_mode_type_ = 
      LunetixDarkModeEngine::DarkModeType::SMART_INVERT;
  
  // Auto dark mode
  bool auto_dark_mode_enabled_ = false;
  int auto_start_hour_ = 20;  // 8 PM
  int auto_end_hour_ = 7;     // 7 AM
  
  // System integration
  bool follow_system_theme_ = true;
  
  // Global exemptions
  std::set<std::string> global_exempt_domains_;
  
  DISALLOW_COPY_AND_ASSIGN(LunetixDarkModeController);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_DARK_MODE_LUNETIX_DARK_MODE_ENGINE_H_