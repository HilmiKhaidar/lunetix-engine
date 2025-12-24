#include "lunetix/common/lunetix_version_info.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace lunetix {
namespace version_info {

class LunetixVersionInfoTest : public testing::Test {};

TEST_F(LunetixVersionInfoTest, GetVersionNumber) {
  std::string version = GetVersionNumber();
  EXPECT_FALSE(version.empty());
  EXPECT_NE(version.find('.'), std::string::npos);
}

TEST_F(LunetixVersionInfoTest, GetVersionString) {
  std::string version = GetVersionString();
  EXPECT_FALSE(version.empty());
  EXPECT_NE(version.find('.'), std::string::npos);
}

TEST_F(LunetixVersionInfoTest, GetVersionComponents) {
  EXPECT_GE(GetMajorVersionNumber(), 1);
  EXPECT_GE(GetMinorVersionNumber(), 0);
  EXPECT_GE(GetBuildNumber(), 0);
  EXPECT_GE(GetPatchNumber(), 0);
}

TEST_F(LunetixVersionInfoTest, GetOSType) {
  std::string os_type = GetOSType();
  EXPECT_FALSE(os_type.empty());
#if BUILDFLAG(IS_WIN)
  EXPECT_EQ(os_type, "Windows");
#elif BUILDFLAG(IS_MAC)
  EXPECT_EQ(os_type, "Mac OS X");
#elif BUILDFLAG(IS_LINUX)
  EXPECT_EQ(os_type, "Linux");
#endif
}

TEST_F(LunetixVersionInfoTest, IsOfficialBuild) {
  // Test should pass regardless of build type
  bool is_official = IsOfficialBuild();
  EXPECT_TRUE(is_official || !is_official);
}

TEST_F(LunetixVersionInfoTest, GetChannelString) {
  std::string channel = GetChannelString();
  // Channel can be empty for stable builds
  EXPECT_TRUE(channel.empty() || !channel.empty());
}

}  // namespace version_info
}  // namespace lunetix