#include "lunetix/browser/net/lunetix_network_delegate.h"

#include "base/strings/string_util.h"
#include "net/base/net_errors.h"
#include "net/http/http_request_headers.h"
#include "net/http/http_response_headers.h"
#include "net/url_request/url_request.h"
#include "lunetix/common/lunetix_constants.h"

namespace lunetix {

LunetixNetworkDelegate::LunetixNetworkDelegate() = default;

LunetixNetworkDelegate::~LunetixNetworkDelegate() = default;

int LunetixNetworkDelegate::OnBeforeURLRequest(net::URLRequest* request,
                                              net::CompletionOnceCallback callback,
                                              GURL* new_url) {
  // Check if request should be blocked
  if (ShouldBlockRequest(request->url())) {
    return net::ERR_BLOCKED_BY_CLIENT;
  }
  
  return ChromeNetworkDelegate::OnBeforeURLRequest(request, std::move(callback), new_url);
}

int LunetixNetworkDelegate::OnBeforeStartTransaction(
    net::URLRequest* request,
    net::CompletionOnceCallback callback,
    net::HttpRequestHeaders* headers) {
  
  // Modify User-Agent header for Lunetix branding
  ModifyUserAgent(headers);
  
  return ChromeNetworkDelegate::OnBeforeStartTransaction(request, std::move(callback), headers);
}

void LunetixNetworkDelegate::OnStartTransaction(
    net::URLRequest* request,
    const net::HttpRequestHeaders& headers) {
  ChromeNetworkDelegate::OnStartTransaction(request, headers);
}

int LunetixNetworkDelegate::OnHeadersReceived(
    net::URLRequest* request,
    net::CompletionOnceCallback callback,
    const net::HttpResponseHeaders* original_response_headers,
    scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
    const net::IPEndPoint& endpoint,
    std::optional<GURL>* preserve_fragment_on_redirect_url) {
  
  return ChromeNetworkDelegate::OnHeadersReceived(
      request, std::move(callback), original_response_headers,
      override_response_headers, endpoint, preserve_fragment_on_redirect_url);
}

void LunetixNetworkDelegate::OnBeforeRedirect(net::URLRequest* request,
                                             const GURL& new_location) {
  ChromeNetworkDelegate::OnBeforeRedirect(request, new_location);
}

void LunetixNetworkDelegate::OnResponseStarted(net::URLRequest* request,
                                              int net_error) {
  ChromeNetworkDelegate::OnResponseStarted(request, net_error);
}

void LunetixNetworkDelegate::OnCompleted(net::URLRequest* request,
                                        bool started,
                                        int net_error) {
  ChromeNetworkDelegate::OnCompleted(request, started, net_error);
}

void LunetixNetworkDelegate::OnURLRequestDestroyed(net::URLRequest* request) {
  ChromeNetworkDelegate::OnURLRequestDestroyed(request);
}

void LunetixNetworkDelegate::OnPACScriptError(int line_number,
                                             const std::u16string& error) {
  ChromeNetworkDelegate::OnPACScriptError(line_number, error);
}

bool LunetixNetworkDelegate::OnCanGetCookies(const net::URLRequest& request,
                                            bool allowed_from_caller) {
  return ChromeNetworkDelegate::OnCanGetCookies(request, allowed_from_caller);
}

bool LunetixNetworkDelegate::OnCanSetCookie(const net::URLRequest& request,
                                           const net::CanonicalCookie& cookie,
                                           net::CookieOptions* options,
                                           bool allowed_from_caller) {
  return ChromeNetworkDelegate::OnCanSetCookie(request, cookie, options, allowed_from_caller);
}

bool LunetixNetworkDelegate::OnCanAccessFile(const net::URLRequest& request,
                                            const base::FilePath& original_path,
                                            const base::FilePath& absolute_path) const {
  return ChromeNetworkDelegate::OnCanAccessFile(request, original_path, absolute_path);
}

void LunetixNetworkDelegate::ModifyUserAgent(net::HttpRequestHeaders* headers) {
  std::string user_agent;
  if (headers->GetHeader(net::HttpRequestHeaders::kUserAgent, &user_agent)) {
    // Replace Chrome with Lunetix in User-Agent string
    base::ReplaceSubstringsAfterOffset(&user_agent, 0, "Chrome", kLunetixUserAgent);
    headers->SetHeader(net::HttpRequestHeaders::kUserAgent, user_agent);
  }
}

bool LunetixNetworkDelegate::ShouldBlockRequest(const GURL& url) {
  // Implement Lunetix-specific request blocking logic
  // For example, block known tracking domains, malware sites, etc.
  
  // Block Google update checks for Chrome
  if (url.host() == "update.googleapis.com" && 
      url.path().find("chrome") != std::string::npos) {
    return true;
  }
  
  // Block Chrome crash reporting
  if (url.host() == "clients2.google.com" && 
      url.path().find("cr/report") != std::string::npos) {
    return true;
  }
  
  return false;
}

}  // namespace lunetix