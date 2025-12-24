#include "lunetix/common/lunetix_paths.h"

#include "base/files/file_path.h"
#include "base/path_service.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace lunetix {

class LunetixPathsTest : public testing::Test {
 protected:
  void SetUp() override {
    RegisterPathProvider();
  }
};

TEST_F(LunetixPathsTest, UserDataDir) {
  base::FilePath user_data_dir;
  EXPECT_TRUE(base::PathService::Get(DIR_USER_DATA, &user_data_dir));
  EXPECT_FALSE(user_data_dir.empty());
  EXPECT_TRUE(user_data_dir.BaseName().LossyDisplayName().find("Lunetix") != std::string::npos);
}

TEST_F(LunetixPathsTest, CrashDumpsDir) {
  base::FilePath crash_dumps_dir;
  EXPECT_TRUE(base::PathService::Get(DIR_CRASH_DUMPS, &crash_dumps_dir));
  EXPECT_FALSE(crash_dumps_dir.empty());
}

TEST_F(LunetixPathsTest, LogsDir) {
  base::FilePath logs_dir;
  EXPECT_TRUE(base::PathService::Get(DIR_LOGS, &logs_dir));
  EXPECT_FALSE(logs_dir.empty());
}

TEST_F(LunetixPathsTest, LunetixExe) {
  base::FilePath lunetix_exe;
  EXPECT_TRUE(base::PathService::Get(FILE_LUNETIX_EXE, &lunetix_exe));
  EXPECT_FALSE(lunetix_exe.empty());
}

TEST_F(LunetixPathsTest, ResourcesPack) {
  base::FilePath resources_pack;
  EXPECT_TRUE(base::PathService::Get(FILE_RESOURCES_PACK, &resources_pack));
  EXPECT_FALSE(resources_pack.empty());
  EXPECT_EQ(resources_pack.BaseName().LossyDisplayName(), "lunetix.pak");
}

}  // namespace lunetix