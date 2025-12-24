#ifndef LUNETIX_BROWSER_NET_LUNETIX_NETWORK_DELEGATE_H_
#define LUNETIX_BROWSER_NET_LUNETIX_NETWORK_DELEGATE_H_

#include "chrome/browser/net/chrome_network_delegate.h"

namespace lunetix {

class LunetixNetworkDelegate : public ChromeNetworkDelegate {
 public:
  LunetixNetworkDelegate();
  ~LunetixNetworkDelegate() override;

  // ChromeNetworkDelegate overrides:
  int OnBeforeURLRequest(net::URLRequest* request,
                        net::CompletionOnceCallback callback,
                        GURL* new_url) override;
  int OnBeforeStartTransaction(net::URLRequest* request,
                              net::CompletionOnceCallback callback,
                              net::HttpRequestHeaders* headers) override;
  void OnStartTransaction(net::URLRequest* request,
                         const net::HttpRequestHeaders& headers) override;
  int OnHeadersReceived(
      net::URLRequest* request,
      net::CompletionOnceCallback callback,
      const net::HttpResponseHeaders* original_response_headers,
      scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
      const net::IPEndPoint& endpoint,
      std::optional<GURL>* preserve_fragment_on_redirect_url) override;
  void OnBeforeRedirect(net::URLRequest* request,
                       const GURL& new_location) override;
  void OnResponseStarted(net::URLRequest* request, int net_error) override;
  void OnCompleted(net::URLRequest* request,
                  bool started,
                  int net_error) override;
  void OnURLRequestDestroyed(net::URLRequest* request) override;
  void OnPACScriptError(int line_number, const std::u16string& error) override;
  bool OnCanGetCookies(const net::URLRequest& request,
                      bool allowed_from_caller) override;
  bool OnCanSetCookie(const net::URLRequest& request,
                     const net::CanonicalCookie& cookie,
                     net::CookieOptions* options,
                     bool allowed_from_caller) override;
  bool OnCanAccessFile(const net::URLRequest& request,
                      const base::FilePath& original_path,
                      const base::FilePath& absolute_path) const override;

 private:
  void ModifyUserAgent(net::HttpRequestHeaders* headers);
  bool ShouldBlockRequest(const GURL& url);
  
  DISALLOW_COPY_AND_ASSIGN(LunetixNetworkDelegate);
};

}  // namespace lunetix

#endif  // LUNETIX_BROWSER_NET_LUNETIX_NETWORK_DELEGATE_H_