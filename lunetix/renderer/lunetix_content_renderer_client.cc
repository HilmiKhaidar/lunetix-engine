#include "lunetix/renderer/lunetix_content_renderer_client.h"

#include "content/public/renderer/render_thread.h"
#include "lunetix/renderer/lunetix_render_thread_observer.h"

namespace lunetix {

LunetixContentRendererClient::LunetixContentRendererClient() = default;

LunetixContentRendererClient::~LunetixContentRendererClient() = default;

void LunetixContentRendererClient::RenderThreadStarted() {
  ChromeContentRendererClient::RenderThreadStarted();
  
  content::RenderThread* thread = content::RenderThread::Get();
  thread->AddObserver(new LunetixRenderThreadObserver());
}

void LunetixContentRendererClient::RenderFrameCreated(
    content::RenderFrame* render_frame) {
  ChromeContentRendererClient::RenderFrameCreated(render_frame);
}

void LunetixContentRendererClient::WebViewCreated(blink::WebView* web_view) {
  ChromeContentRendererClient::WebViewCreated(web_view);
}

}  // namespace lunetix