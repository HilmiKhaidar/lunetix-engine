#include "lunetix/browser/reading_mode/lunetix_reading_mode.h"

#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/web_contents.h"

namespace lunetix {

// LunetixReadingMode implementation

LunetixReadingMode::LunetixReadingMode(content::WebContents* web_contents)
    : content::WebContentsObserver(web_contents) {}

LunetixReadingMode::~LunetixReadingMode() = default;

void LunetixReadingMode::EnterReadingMode() {
  if (is_reading_mode_active_) {
    return;
  }
  
  if (!IsPageReadable()) {
    return;
  }
  
  is_reading_mode_active_ = true;
  ExtractReadableContent();
  InjectReadingModeCSS();
  InjectReadingModeJS();
  ApplyReadingModeStyles();
}

void LunetixReadingMode::ExitReadingMode() {
  if (!is_reading_mode_active_) {
    return;
  }
  
  is_reading_mode_active_ = false;
  RemoveReadingModeStyles();
  
  // Reload the page to restore original content
  web_contents()->GetController().Reload(content::ReloadType::NORMAL, false);
}

void LunetixReadingMode::SetFontSize(int font_size) {
  font_size_ = std::max(10, std::min(32, font_size));
  if (is_reading_mode_active_) {
    ApplyReadingModeStyles();
  }
}

void LunetixReadingMode::SetFontFamily(const std::string& font_family) {
  font_family_ = font_family;
  if (is_reading_mode_active_) {
    ApplyReadingModeStyles();
  }
}

void LunetixReadingMode::SetLineHeight(double line_height) {
  line_height_ = std::max(1.0, std::min(3.0, line_height));
  if (is_reading_mode_active_) {
    ApplyReadingModeStyles();
  }
}

void LunetixReadingMode::SetTextColor(const std::string& color) {
  text_color_ = color;
  if (is_reading_mode_active_) {
    ApplyReadingModeStyles();
  }
}

void LunetixReadingMode::SetBackgroundColor(const std::string& color) {
  background_color_ = color;
  if (is_reading_mode_active_) {
    ApplyReadingModeStyles();
  }
}

void LunetixReadingMode::SetPageWidth(int width_percentage) {
  page_width_percentage_ = std::max(50, std::min(100, width_percentage));
  if (is_reading_mode_active_) {
    ApplyReadingModeStyles();
  }
}

void LunetixReadingMode::SetTheme(Theme theme) {
  current_theme_ = theme;
  
  switch (theme) {
    case Theme::LIGHT:
      text_color_ = "#333333";
      background_color_ = "#ffffff";
      break;
    case Theme::DARK:
      text_color_ = "#e0e0e0";
      background_color_ = "#1a1a1a";
      break;
    case Theme::SEPIA:
      text_color_ = "#5c4b37";
      background_color_ = "#f4f1ea";
      break;
    case Theme::HIGH_CONTRAST:
      text_color_ = "#000000";
      background_color_ = "#ffffff";
      break;
  }
  
  if (is_reading_mode_active_) {
    ApplyReadingModeStyles();
  }
}

void LunetixReadingMode::DidFinishNavigation(content::NavigationHandle* navigation_handle) {
  if (navigation_handle->IsInMainFrame() && navigation_handle->HasCommitted()) {
    if (is_reading_mode_active_) {
      ExitReadingMode();
    }
  }
}

void LunetixReadingMode::DocumentOnLoadCompletedInMainFrame() {
  // Auto-enter reading mode if enabled and page is suitable
  LunetixReadingModeController* controller = LunetixReadingModeController::GetInstance();
  if (controller->IsAutoEnterEnabled() && IsPageReadable()) {
    EnterReadingMode();
  }
}

void LunetixReadingMode::ExtractReadableContent() {
  if (content_extraction_in_progress_) {
    return;
  }
  
  content_extraction_in_progress_ = true;
  
  // JavaScript to extract readable content using Readability.js-like algorithm
  std::string extraction_script = R"(
    (function() {
      // Simple content extraction algorithm
      var article = document.querySelector('article') || 
                   document.querySelector('[role="main"]') ||
                   document.querySelector('.content') ||
                   document.querySelector('#content') ||
                   document.querySelector('.post') ||
                   document.querySelector('.entry');
      
      if (!article) {
        // Find the element with most text content
        var candidates = document.querySelectorAll('div, section, main');
        var bestCandidate = null;
        var maxTextLength = 0;
        
        for (var i = 0; i < candidates.length; i++) {
          var textLength = candidates[i].innerText.length;
          if (textLength > maxTextLength) {
            maxTextLength = textLength;
            bestCandidate = candidates[i];
          }
        }
        article = bestCandidate;
      }
      
      if (!article) return null;
      
      var title = document.querySelector('h1') ? document.querySelector('h1').innerText : document.title;
      var author = '';
      var authorEl = document.querySelector('[rel="author"]') || 
                    document.querySelector('.author') ||
                    document.querySelector('.byline');
      if (authorEl) author = authorEl.innerText;
      
      var content = article.innerHTML;
      var textContent = article.innerText;
      var wordCount = textContent.split(/\s+/).length;
      var readingTime = Math.ceil(wordCount / 200); // 200 words per minute
      
      return {
        title: title,
        author: author,
        content: content,
        wordCount: wordCount,
        readingTime: readingTime
      };
    })();
  )";
  
  web_contents()->GetMainFrame()->ExecuteJavaScript(
      base::UTF8ToUTF16(extraction_script),
      base::BindOnce(&LunetixReadingMode::OnContentExtracted,
                     weak_factory_.GetWeakPtr(), "", "", "", 0));
}

void LunetixReadingMode::InjectReadingModeCSS() {
  std::string css = GenerateReadingModeCSS();
  std::string script = "var style = document.createElement('style');"
                      "style.id = 'lunetix-reading-mode-css';"
                      "style.textContent = `" + css + "`;"
                      "document.head.appendChild(style);";
  
  web_contents()->GetMainFrame()->ExecuteJavaScript(
      base::UTF8ToUTF16(script), base::DoNothing());
}

void LunetixReadingMode::InjectReadingModeJS() {
  std::string js = GenerateReadingModeJS();
  web_contents()->GetMainFrame()->ExecuteJavaScript(
      base::UTF8ToUTF16(js), base::DoNothing());
}

void LunetixReadingMode::ApplyReadingModeStyles() {
  InjectReadingModeCSS();
}

void LunetixReadingMode::RemoveReadingModeStyles() {
  std::string script = "var style = document.getElementById('lunetix-reading-mode-css');"
                      "if (style) style.remove();"
                      "document.body.classList.remove('lunetix-reading-mode');";
  
  web_contents()->GetMainFrame()->ExecuteJavaScript(
      base::UTF8ToUTF16(script), base::DoNothing());
}

bool LunetixReadingMode::IsPageReadable() {
  // Simple heuristic - check if page has enough text content
  // In a real implementation, this would be more sophisticated
  return true;
}

std::string LunetixReadingMode::GenerateReadingModeCSS() {
  return R"(
    body.lunetix-reading-mode {
      font-family: )" + font_family_ + R"( !important;
      font-size: )" + std::to_string(font_size_) + R"(px !important;
      line-height: )" + std::to_string(line_height_) + R"( !important;
      color: )" + text_color_ + R"( !important;
      background-color: )" + background_color_ + R"( !important;
      margin: 0 !important;
      padding: 20px !important;
    }
    
    body.lunetix-reading-mode * {
      max-width: none !important;
      width: auto !important;
      height: auto !important;
      margin: 0 !important;
      padding: 0 !important;
      border: none !important;
      background: transparent !important;
      color: inherit !important;
      font-family: inherit !important;
      font-size: inherit !important;
      line-height: inherit !important;
    }
    
    body.lunetix-reading-mode .lunetix-reading-content {
      max-width: )" + std::to_string(page_width_percentage_) + R"(% !important;
      margin: 0 auto !important;
      padding: 40px 20px !important;
    }
    
    body.lunetix-reading-mode h1, 
    body.lunetix-reading-mode h2, 
    body.lunetix-reading-mode h3 {
      font-weight: bold !important;
      margin: 1.5em 0 0.5em 0 !important;
    }
    
    body.lunetix-reading-mode h1 { font-size: 1.8em !important; }
    body.lunetix-reading-mode h2 { font-size: 1.5em !important; }
    body.lunetix-reading-mode h3 { font-size: 1.3em !important; }
    
    body.lunetix-reading-mode p {
      margin: 1em 0 !important;
      text-align: justify !important;
    }
    
    body.lunetix-reading-mode img {
      max-width: 100% !important;
      height: auto !important;
      margin: 1em 0 !important;
      display: block !important;
    }
    
    body.lunetix-reading-mode a {
      color: #0066cc !important;
      text-decoration: underline !important;
    }
    
    body.lunetix-reading-mode blockquote {
      margin: 1em 0 !important;
      padding-left: 1em !important;
      border-left: 3px solid #ccc !important;
      font-style: italic !important;
    }
  )";
}

std::string LunetixReadingMode::GenerateReadingModeJS() {
  return R"(
    (function() {
      // Hide all elements except the main content
      var allElements = document.querySelectorAll('*');
      for (var i = 0; i < allElements.length; i++) {
        var el = allElements[i];
        if (el.tagName !== 'HTML' && el.tagName !== 'HEAD' && el.tagName !== 'BODY') {
          if (!el.closest('.lunetix-reading-content')) {
            el.style.display = 'none';
          }
        }
      }
      
      // Add reading mode class to body
      document.body.classList.add('lunetix-reading-mode');
      
      // Create reading content container
      var content = document.querySelector('article') || 
                   document.querySelector('[role="main"]') ||
                   document.querySelector('.content') ||
                   document.querySelector('#content');
      
      if (content) {
        var container = document.createElement('div');
        container.className = 'lunetix-reading-content';
        container.innerHTML = content.innerHTML;
        document.body.innerHTML = '';
        document.body.appendChild(container);
      }
    })();
  )";
}

void LunetixReadingMode::OnContentExtracted(const std::string& title,
                                           const std::string& author,
                                           const std::string& content,
                                           int reading_time) {
  extracted_content_.title = title;
  extracted_content_.author = author;
  extracted_content_.content = content;
  extracted_content_.estimated_reading_time_minutes = reading_time;
  
  content_extraction_in_progress_ = false;
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(LunetixReadingMode);

// LunetixReadingModeController implementation

LunetixReadingModeController* LunetixReadingModeController::GetInstance() {
  static LunetixReadingModeController instance;
  return &instance;
}

LunetixReadingModeController::LunetixReadingModeController() = default;

LunetixReadingModeController::~LunetixReadingModeController() = default;

void LunetixReadingModeController::SetDefaultFontSize(int font_size) {
  default_font_size_ = font_size;
}

void LunetixReadingModeController::SetDefaultFontFamily(const std::string& font_family) {
  default_font_family_ = font_family;
}

void LunetixReadingModeController::SetDefaultTheme(LunetixReadingMode::Theme theme) {
  default_theme_ = theme;
}

void LunetixReadingModeController::SetAutoEnterReadingMode(bool enabled) {
  auto_enter_enabled_ = enabled;
}

void LunetixReadingModeController::SetMinimumWordCount(int word_count) {
  minimum_word_count_ = word_count;
}

bool LunetixReadingModeController::IsReadingModeAvailable(content::WebContents* web_contents) {
  if (!web_contents) {
    return false;
  }
  
  // Check if the current page is suitable for reading mode
  // This would typically check content type, word count, etc.
  return true;
}

void LunetixReadingModeController::ToggleReadingMode(content::WebContents* web_contents) {
  if (!web_contents) {
    return;
  }
  
  LunetixReadingMode* reading_mode = 
      LunetixReadingMode::FromWebContents(web_contents);
  
  if (!reading_mode) {
    LunetixReadingMode::CreateForWebContents(web_contents);
    reading_mode = LunetixReadingMode::FromWebContents(web_contents);
  }
  
  if (reading_mode) {
    if (reading_mode->IsInReadingMode()) {
      reading_mode->ExitReadingMode();
    } else {
      reading_mode->EnterReadingMode();
    }
  }
}

}  // namespace lunetix