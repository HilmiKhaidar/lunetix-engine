#include "lunetix/renderer/lunetix_render_thread_observer.h"

namespace lunetix {

LunetixRenderThreadObserver::LunetixRenderThreadObserver() = default;

LunetixRenderThreadObserver::~LunetixRenderThreadObserver() = default;

void LunetixRenderThreadObserver::RegisterMojoInterfaces(
    blink::AssociatedInterfaceRegistry* associated_interfaces) {
  // Register Lunetix-specific Mojo interfaces here
}

void LunetixRenderThreadObserver::UnregisterMojoInterfaces(
    blink::AssociatedInterfaceRegistry* associated_interfaces) {
  // Unregister Lunetix-specific Mojo interfaces here
}

}  // namespace lunetix