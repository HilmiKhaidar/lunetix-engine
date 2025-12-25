#include "lunetix/browser/dark_mode/lunetix_dark_mode_engine.h"

#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/web_contents.h"
#include "url/gurl.h"

namespace lunetix {

// LunetixDarkModeEngine implementation

LunetixDarkModeEngine::LunetixDarkModeEngine(content::WebContents* web_contents)
    : content::WebContentsObserver(web_contents) {
  
  // Add common exemptions
  exempt_domains_.insert("youtube.com");
  exempt_domains_.insert("netflix.com");
  exempt_domains_.insert("twitch.tv");
  exempt_domains_.insert("instagram.com");
}

LunetixDarkModeEngine::~LunetixDarkModeEngine() = default;

void LunetixDarkModeEngine::EnableDarkMode() {
  if (is_dark_mode_enabled_) {
    return;
  }
  
  is_dark_mode_enabled_ = true;
  
  if (ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::DisableDarkMode() {
  if (!is_dark_mode_enabled_) {
    return;
  }
  
  is_dark_mode_enabled_ = false;
  RemoveDarkMode();
}

void LunetixDarkModeEngine::ToggleDarkMode() {
  if (is_dark_mode_enabled_) {
    DisableDarkMode();
  } else {
    EnableDarkMode();
  }
}

void LunetixDarkModeEngine::SetDarkModeType(DarkModeType type) {
  dark_mode_type_ = type;
  
  if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::SetBrightness(double brightness) {
  brightness_ = std::max(0.0, std::min(2.0, brightness));
  
  if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::SetContrast(double contrast) {
  contrast_ = std::max(0.0, std::min(2.0, contrast));
  
  if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::SetSepia(double sepia) {
  sepia_ = std::max(0.0, std::min(1.0, sepia));
  
  if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::SetHueRotate(int degrees) {
  hue_rotate_ = degrees % 360;
  
  if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::SetSiteExemption(const std::string& domain, bool exempt) {
  if (exempt) {
    exempt_domains_.insert(domain);
  } else {
    exempt_domains_.erase(domain);
  }
  
  // Reapply dark mode based on new exemption status
  if (is_dark_mode_enabled_) {
    if (ShouldApplyDarkMode()) {
      ApplyDarkMode();
    } else {
      RemoveDarkMode();
    }
  }
}

bool LunetixDarkModeEngine::IsSiteExempt(const std::string& domain) const {
  return exempt_domains_.find(domain) != exempt_domains_.end();
}

void LunetixDarkModeEngine::ClearSiteExemptions() {
  exempt_domains_.clear();
}

void LunetixDarkModeEngine::SetPreserveImages(bool preserve) {
  preserve_images_ = preserve;
  
  if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::SetPreserveVideos(bool preserve) {
  preserve_videos_ = preserve;
  
  if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::DidFinishNavigation(content::NavigationHandle* navigation_handle) {
  if (navigation_handle->IsInMainFrame() && navigation_handle->HasCommitted()) {
    if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
      // Delay application to ensure page is fully loaded
      base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
          FROM_HERE,
          base::BindOnce(&LunetixDarkModeEngine::ApplyDarkMode,
                         weak_factory_.GetWeakPtr()),
          base::Milliseconds(100));
    }
  }
}

void LunetixDarkModeEngine::DocumentOnLoadCompletedInMainFrame() {
  if (is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::DidFinishLoad(content::RenderFrameHost* render_frame_host,
                                         const GURL& validated_url) {
  if (render_frame_host->IsInPrimaryMainFrame() && 
      is_dark_mode_enabled_ && ShouldApplyDarkMode()) {
    ApplyDarkMode();
  }
}

void LunetixDarkModeEngine::ApplyDarkMode() {
  RemoveDarkMode();  // Remove any existing dark mode first
  InjectDarkModeCSS();
  InjectDarkModeJS();
}

void LunetixDarkModeEngine::RemoveDarkMode() {
  std::string script = R"(
    // Remove dark mode styles
    var darkModeStyle = document.getElementById('lunetix-dark-mode-css');
    if (darkModeStyle) {
      darkModeStyle.remove();
    }
    
    // Remove dark mode class
    document.documentElement.classList.remove('lunetix-dark-mode');
    document.body.classList.remove('lunetix-dark-mode');
  )";
  
  web_contents()->GetMainFrame()->ExecuteJavaScript(
      base::UTF8ToUTF16(script), base::DoNothing());
}

void LunetixDarkModeEngine::InjectDarkModeCSS() {
  std::string css;
  
  switch (dark_mode_type_) {
    case DarkModeType::SIMPLE_INVERT:
      css = GenerateSimpleInvertCSS();
      break;
    case DarkModeType::SMART_INVERT:
      css = GenerateSmartInvertCSS();
      break;
    case DarkModeType::CSS_FILTER:
      css = GenerateCSSFilterCSS();
      break;
    case DarkModeType::CUSTOM_CSS:
      css = GenerateCustomDarkCSS();
      break;
    case DarkModeType::AUTO_DETECT:
      css = GenerateSmartInvertCSS();  // Default to smart invert
      break;
  }
  
  std::string script = R"(
    var style = document.createElement('style');
    style.id = 'lunetix-dark-mode-css';
    style.textContent = `)" + css + R"(`;
    document.head.appendChild(style);
    
    document.documentElement.classList.add('lunetix-dark-mode');
    document.body.classList.add('lunetix-dark-mode');
  )";
  
  web_contents()->GetMainFrame()->ExecuteJavaScript(
      base::UTF8ToUTF16(script), base::DoNothing());
}

void LunetixDarkModeEngine::InjectDarkModeJS() {
  std::string js = GenerateDarkModeJS();
  web_contents()->GetMainFrame()->ExecuteJavaScript(
      base::UTF8ToUTF16(js), base::DoNothing());
}

std::string LunetixDarkModeEngine::GenerateSimpleInvertCSS() {
  return R"(
    html.lunetix-dark-mode {
      filter: invert(1) hue-rotate(180deg) !important;
    }
    
    html.lunetix-dark-mode img,
    html.lunetix-dark-mode video,
    html.lunetix-dark-mode iframe,
    html.lunetix-dark-mode svg,
    html.lunetix-dark-mode canvas {
      filter: invert(1) hue-rotate(180deg) !important;
    }
  )";
}

std::string LunetixDarkModeEngine::GenerateSmartInvertCSS() {
  std::string preserve_media = preserve_images_ ? 
      "html.lunetix-dark-mode img { filter: invert(1) hue-rotate(180deg) !important; }" : "";
  
  if (preserve_videos_) {
    preserve_media += "html.lunetix-dark-mode video { filter: invert(1) hue-rotate(180deg) !important; }";
  }
  
  return R"(
    html.lunetix-dark-mode {
      filter: invert()" + std::to_string(brightness_) + R"() 
              contrast()" + std::to_string(contrast_) + R"() 
              sepia()" + std::to_string(sepia_) + R"() 
              hue-rotate()" + std::to_string(hue_rotate_) + R"(deg) !important;
    }
    
    )" + preserve_media + R"(
    
    html.lunetix-dark-mode [style*="background-image"] {
      filter: invert(1) hue-rotate(180deg) !important;
    }
  )";
}

std::string LunetixDarkModeEngine::GenerateCSSFilterCSS() {
  return R"(
    html.lunetix-dark-mode {
      filter: brightness()" + std::to_string(brightness_) + R"() 
              contrast()" + std::to_string(contrast_) + R"() 
              sepia()" + std::to_string(sepia_) + R"() 
              hue-rotate()" + std::to_string(hue_rotate_) + R"(deg) 
              invert(0.9) !important;
    }
  )";
}

std::string LunetixDarkModeEngine::GenerateCustomDarkCSS() {
  return R"(
    html.lunetix-dark-mode {
      background-color: #1a1a1a !important;
      color: #e0e0e0 !important;
    }
    
    html.lunetix-dark-mode body {
      background-color: #1a1a1a !important;
      color: #e0e0e0 !important;
    }
    
    html.lunetix-dark-mode div,
    html.lunetix-dark-mode span,
    html.lunetix-dark-mode p,
    html.lunetix-dark-mode h1, html.lunetix-dark-mode h2, 
    html.lunetix-dark-mode h3, html.lunetix-dark-mode h4,
    html.lunetix-dark-mode h5, html.lunetix-dark-mode h6 {
      background-color: transparent !important;
      color: #e0e0e0 !important;
    }
    
    html.lunetix-dark-mode a {
      color: #66b3ff !important;
    }
    
    html.lunetix-dark-mode input,
    html.lunetix-dark-mode textarea,
    html.lunetix-dark-mode select {
      background-color: #2d2d2d !important;
      color: #e0e0e0 !important;
      border-color: #555 !important;
    }
    
    html.lunetix-dark-mode button {
      background-color: #404040 !important;
      color: #e0e0e0 !important;
      border-color: #666 !important;
    }
  )";
}

std::string LunetixDarkModeEngine::GenerateDarkModeJS() {
  return R"(
    (function() {
      // Monitor for dynamically added content
      var observer = new MutationObserver(function(mutations) {
        mutations.forEach(function(mutation) {
          if (mutation.type === 'childList') {
            mutation.addedNodes.forEach(function(node) {
              if (node.nodeType === Node.ELEMENT_NODE) {
                // Apply dark mode to new elements if needed
                // This is where additional processing could be added
              }
            });
          }
        });
      });
      
      observer.observe(document.body, {
        childList: true,
        subtree: true
      });
      
      // Store observer for cleanup
      window.lunetixDarkModeObserver = observer;
    })();
  )";
}

bool LunetixDarkModeEngine::ShouldApplyDarkMode() {
  std::string domain = GetCurrentDomain();
  
  // Check site exemptions
  if (IsSiteExempt(domain)) {
    return false;
  }
  
  // Check global exemptions
  LunetixDarkModeController* controller = LunetixDarkModeController::GetInstance();
  if (controller->IsGloballyExempt(domain)) {
    return false;
  }
  
  return true;
}

std::string LunetixDarkModeEngine::GetCurrentDomain() {
  GURL url = web_contents()->GetLastCommittedURL();
  return url.host();
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(LunetixDarkModeEngine);

// LunetixDarkModeController implementation

LunetixDarkModeController* LunetixDarkModeController::GetInstance() {
  static LunetixDarkModeController instance;
  return &instance;
}

LunetixDarkModeController::LunetixDarkModeController() {
  // Add common global exemptions
  global_exempt_domains_.insert("maps.google.com");
  global_exempt_domains_.insert("earth.google.com");
  global_exempt_domains_.insert("photos.google.com");
}

LunetixDarkModeController::~LunetixDarkModeController() = default;

void LunetixDarkModeController::SetGlobalDarkModeEnabled(bool enabled) {
  global_dark_mode_enabled_ = enabled;
  
  if (enabled) {
    ApplyDarkModeToAllTabs();
  } else {
    RemoveDarkModeFromAllTabs();
  }
}

void LunetixDarkModeController::SetDefaultDarkModeType(LunetixDarkModeEngine::DarkModeType type) {
  default_dark_mode_type_ = type;
}

LunetixDarkModeEngine::DarkModeType LunetixDarkModeController::GetDefaultDarkModeType() const {
  return default_dark_mode_type_;
}

void LunetixDarkModeController::SetAutoDarkModeEnabled(bool enabled) {
  auto_dark_mode_enabled_ = enabled;
  
  if (enabled) {
    UpdateAutoDarkMode();
  }
}

void LunetixDarkModeController::SetAutoDarkModeSchedule(int start_hour, int end_hour) {
  auto_start_hour_ = std::max(0, std::min(23, start_hour));
  auto_end_hour_ = std::max(0, std::min(23, end_hour));
}

void LunetixDarkModeController::GetAutoDarkModeSchedule(int* start_hour, int* end_hour) const {
  *start_hour = auto_start_hour_;
  *end_hour = auto_end_hour_;
}

void LunetixDarkModeController::SetFollowSystemTheme(bool follow) {
  follow_system_theme_ = follow;
  
  if (follow) {
    CheckSystemTheme();
  }
}

void LunetixDarkModeController::ApplyDarkModeToAllTabs() {
  // Implementation would iterate through all browser windows and tabs
  // This is a simplified version
}

void LunetixDarkModeController::RemoveDarkModeFromAllTabs() {
  // Implementation would iterate through all browser windows and tabs
  // This is a simplified version
}

void LunetixDarkModeController::AddGlobalSiteExemption(const std::string& domain) {
  global_exempt_domains_.insert(domain);
}

void LunetixDarkModeController::RemoveGlobalSiteExemption(const std::string& domain) {
  global_exempt_domains_.erase(domain);
}

bool LunetixDarkModeController::IsGloballyExempt(const std::string& domain) const {
  return global_exempt_domains_.find(domain) != global_exempt_domains_.end();
}

int LunetixDarkModeController::GetDarkModeEnabledTabsCount() const {
  // Implementation would count tabs with dark mode enabled
  return 0;
}

void LunetixDarkModeController::CheckSystemTheme() {
  // Implementation would check system theme and apply accordingly
}

void LunetixDarkModeController::UpdateAutoDarkMode() {
  // Implementation would check current time and apply/remove dark mode
}

}  // namespace lunetix