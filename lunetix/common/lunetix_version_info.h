#ifndef LUNETIX_COMMON_LUNETIX_VERSION_INFO_H_
#define LUNETIX_COMMON_LUNETIX_VERSION_INFO_H_

#include <string>

namespace lunetix {
namespace version_info {

std::string GetVersionNumber();
std::string GetVersionString();
std::string GetVersionStringWithModifier();
std::string GetLastChange();
bool IsOfficialBuild();
std::string GetOSType();
std::string GetChannelString();

int GetMajorVersionNumber();
int GetMinorVersionNumber();
int GetBuildNumber();
int GetPatchNumber();

}  // namespace version_info
}  // namespace lunetix

#endif  // LUNETIX_COMMON_LUNETIX_VERSION_INFO_H_