#ifndef LUNETIX_RENDERER_LUNETIX_RENDER_THREAD_OBSERVER_H_
#define LUNETIX_RENDERER_LUNETIX_RENDER_THREAD_OBSERVER_H_

#include "content/public/renderer/render_thread_observer.h"

namespace lunetix {

class LunetixRenderThreadObserver : public content::RenderThreadObserver {
 public:
  LunetixRenderThreadObserver();
  ~LunetixRenderThreadObserver() override;

  // content::RenderThreadObserver overrides:
  void RegisterMojoInterfaces(
      blink::AssociatedInterfaceRegistry* associated_interfaces) override;
  void UnregisterMojoInterfaces(
      blink::AssociatedInterfaceRegistry* associated_interfaces) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixRenderThreadObserver);
};

}  // namespace lunetix

#endif  // LUNETIX_RENDERER_LUNETIX_RENDER_THREAD_OBSERVER_H_