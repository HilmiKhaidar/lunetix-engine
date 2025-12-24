#ifndef LUNETIX_UTILITY_LUNETIX_CONTENT_UTILITY_CLIENT_H_
#define LUNETIX_UTILITY_LUNETIX_CONTENT_UTILITY_CLIENT_H_

#include "chrome/utility/chrome_content_utility_client.h"

namespace lunetix {

class LunetixContentUtilityClient : public ChromeContentUtilityClient {
 public:
  LunetixContentUtilityClient();
  ~LunetixContentUtilityClient() override;

  // ChromeContentUtilityClient overrides:
  void UtilityThreadStarted() override;
  void RegisterMainThreadServices(mojo::ServiceFactory& services) override;
  void RegisterIOThreadServices(mojo::ServiceFactory& services) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(LunetixContentUtilityClient);
};

}  // namespace lunetix

#endif  // LUNETIX_UTILITY_LUNETIX_CONTENT_UTILITY_CLIENT_H_