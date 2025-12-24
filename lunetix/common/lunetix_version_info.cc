#include "lunetix/common/lunetix_version_info.h"

#include "base/strings/string_number_conversions.h"
#include "base/strings/stringprintf.h"
#include "build/build_config.h"
#include "lunetix/common/lunetix_constants.h"

namespace lunetix {
namespace version_info {

std::string GetVersionNumber() {
  return base::StringPrintf("%d.%d.%d.%d",
                           LUNETIX_VERSION_MAJOR,
                           LUNETIX_VERSION_MINOR,
                           LUNETIX_VERSION_BUILD,
                           LUNETIX_VERSION_PATCH);
}

std::string GetVersionString() {
  std::string version = GetVersionNumber();
#if defined(LUNETIX_CHANNEL)
  if (strlen(LUNETIX_CHANNEL) > 0) {
    version += " " + std::string(LUNETIX_CHANNEL);
  }
#endif
  return version;
}

std::string GetVersionStringWithModifier() {
  std::string version = GetVersionString();
#if !defined(OFFICIAL_BUILD)
  version += " (Developer Build)";
#endif
  return version;
}

std::string GetLastChange() {
  return "unknown";
}

bool IsOfficialBuild() {
#if defined(OFFICIAL_BUILD)
  return true;
#else
  return false;
#endif
}

std::string GetOSType() {
#if BUILDFLAG(IS_WIN)
  return "Windows";
#elif BUILDFLAG(IS_MAC)
  return "Mac OS X";
#elif BUILDFLAG(IS_LINUX)
  return "Linux";
#else
  return "Unknown";
#endif
}

std::string GetChannelString() {
#if defined(LUNETIX_CHANNEL)
  return LUNETIX_CHANNEL;
#else
  return "";
#endif
}

int GetMajorVersionNumber() {
  return LUNETIX_VERSION_MAJOR;
}

int GetMinorVersionNumber() {
  return LUNETIX_VERSION_MINOR;
}

int GetBuildNumber() {
  return LUNETIX_VERSION_BUILD;
}

int GetPatchNumber() {
  return LUNETIX_VERSION_PATCH;
}

}  // namespace version_info
}  // namespace lunetix