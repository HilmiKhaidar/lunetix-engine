#include "lunetix/utility/lunetix_content_utility_client.h"

namespace lunetix {

LunetixContentUtilityClient::LunetixContentUtilityClient() = default;

LunetixContentUtilityClient::~LunetixContentUtilityClient() = default;

void LunetixContentUtilityClient::UtilityThreadStarted() {
  ChromeContentUtilityClient::UtilityThreadStarted();
}

void LunetixContentUtilityClient::RegisterMainThreadServices(
    mojo::ServiceFactory& services) {
  ChromeContentUtilityClient::RegisterMainThreadServices(services);
}

void LunetixContentUtilityClient::RegisterIOThreadServices(
    mojo::ServiceFactory& services) {
  ChromeContentUtilityClient::RegisterIOThreadServices(services);
}

}  // namespace lunetix