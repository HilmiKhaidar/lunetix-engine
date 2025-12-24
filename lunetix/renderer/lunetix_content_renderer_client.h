#ifndef LUNETIX_RENDERER_LUNETIX_CONTENT_RENDERER_CLIENT_H_
#define LUNETIX_RENDERER_LUNETIX_CONTENT_RENDERER_CLIENT_H_

#include "chrome/renderer/chrome_content_renderer_client.h"

namespace lunetix {

class LunetixContentRendererClient : public ChromeContentRendererClient {
 public:
  LunetixContentRendererClient();
  ~LunetixContentRendererClient() override;

  // ChromeContentRendererClient overrides:
  void RenderThreadStarted() override;
  void RenderFrameCreated(content::RenderFrame* render_frame) override;
  void WebViewCreated(blink::WebView* web_view) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixContentRendererClient);
};

}  // namespace lunetix

#endif  // LUNETIX_RENDERER_LUNETIX_CONTENT_RENDERER_CLIENT_H_