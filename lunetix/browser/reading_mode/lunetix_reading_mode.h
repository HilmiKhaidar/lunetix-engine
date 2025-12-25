#ifndef LUNETIX_BROWSER_READING_MODE_LUNETIX_READING_MODE_H_
#define LUNETIX_BROWSER_READING_MODE_LUNETIX_READING_MODE_H_

#include "base/memory/weak_ptr.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace content {
class WebContents;
}

namespace lunetix {

class LunetixReadingMode : public content::WebContentsObserver,
                          public content::WebContentsUserData<LunetixReadingMode> {
 public:
  ~LunetixReadingMode() override;

  // Reading mode control
  void EnterReadingMode();
  void ExitReadingMode();
  bool IsInReadingMode() const { return is_reading_mode_active_; }
  
  // Reading mode settings
  void SetFontSize(int font_size);
  void SetFontFamily(const std::string& font_family);
  void SetLineHeight(double line_height);
  void SetTextColor(const std::string& color);
  void SetBackgroundColor(const std::string& color);
  void SetPageWidth(int width_percentage);
  
  // Theme presets
  enum class Theme {
    LIGHT,
    DARK,
    SEPIA,
    HIGH_CONTRAST
  };
  
  void SetTheme(Theme theme);
  Theme GetCurrentTheme() const { return current_theme_; }
  
  // Content extraction
  struct ReadingContent {
    std::string title;
    std::string author;
    std::string content;
    std::string excerpt;
    int estimated_reading_time_minutes;
    std::vector<std::string> images;
  };
  
  const ReadingContent& GetExtractedContent() const { return extracted_content_; }
  
  // WebContentsObserver overrides:
  void DidFinishNavigation(content::NavigationHandle* navigation_handle) override;
  void DocumentOnLoadCompletedInMainFrame() override;
  
 private:
  friend class content::WebContentsUserData<LunetixReadingMode>;
  
  explicit LunetixReadingMode(content::WebContents* web_contents);
  
  void ExtractReadableContent();
  void InjectReadingModeCSS();
  void InjectReadingModeJS();
  void ApplyReadingModeStyles();
  void RemoveReadingModeStyles();
  
  bool IsPageReadable();
  std::string GenerateReadingModeCSS();
  std::string GenerateReadingModeJS();
  
  void OnContentExtracted(const std::string& title,
                         const std::string& author,
                         const std::string& content,
                         int reading_time);
  
  // Settings
  int font_size_ = 16;
  std::string font_family_ = "Georgia, serif";
  double line_height_ = 1.6;
  std::string text_color_ = "#333333";
  std::string background_color_ = "#ffffff";
  int page_width_percentage_ = 70;
  Theme current_theme_ = Theme::LIGHT;
  
  // State
  bool is_reading_mode_active_ = false;
  bool content_extraction_in_progress_ = false;
  ReadingContent extracted_content_;
  
  WEB_CONTENTS_USER_DATA_KEY_DECL();
  
  base::WeakPtrFactory<LunetixReadingMode> weak_factory_{this};
  
  DISALLOW_COPY_AND_ASSIGN(LunetixReadingMode);
};

class LunetixReadingModeController {
 public:
  static LunetixReadingModeController* GetInstance();
  
  // Global reading mode settings
  void SetDefaultFontSize(int font_size);
  void SetDefaultFontFamily(const std::string& font_family);
  void SetDefaultTheme(LunetixReadingMode::Theme theme);
  
  // Auto-detection settings
  void SetAutoEnterReadingMode(bool enabled);
  bool IsAutoEnterEnabled() const { return auto_enter_enabled_; }
  
  void SetMinimumWordCount(int word_count);
  int GetMinimumWordCount() const { return minimum_word_count_; }
  
  // Reading mode availability
  bool IsReadingModeAvailable(content::WebContents* web_contents);
  void ToggleReadingMode(content::WebContents* web_contents);
  
 private:
  LunetixReadingModeController();
  ~LunetixReadingModeController();
  
  // Default settings
  int default_font_size_ = 16;
  std::string default_font_family_ = "Georgia, serif";
  LunetixReadingMode::Theme default_theme_ = LunetixReadingMode::Theme::LIGHT;
  
  // Auto-detection settings
  bool auto_enter_enabled_ = false;
  int minimum_word_count_ = 500;
  
  DISALLOW_COPY_AND_ASSIGN(LunetixReadingModeController);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_READING_MODE_LUNETIX_READING_MODE_H_