#include "lunetix/common/lunetix_paths.h"

#include "base/environment.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/path_service.h"
#include "base/system/sys_info.h"
#include "build/build_config.h"
#include "chrome/common/chrome_paths.h"
#include "lunetix/common/lunetix_constants.h"

#if BUILDFLAG(IS_WIN)
#include "base/win/registry.h"
#include "base/win/windows_version.h"
#endif

namespace lunetix {

namespace {

bool PathProvider(int key, base::FilePath* result) {
  base::FilePath cur;
  
  switch (key) {
    case DIR_USER_DATA:
      if (!base::PathService::Get(base::DIR_LOCAL_APP_DATA, &cur))
        return false;
      cur = cur.Append(FILE_PATH_LITERAL(kLunetixUserDataDirname));
      break;
      
    case DIR_CRASH_DUMPS:
      if (!base::PathService::Get(DIR_USER_DATA, &cur))
        return false;
      cur = cur.Append(FILE_PATH_LITERAL("Crashpad"));
      break;
      
    case DIR_LOGS:
      if (!base::PathService::Get(DIR_USER_DATA, &cur))
        return false;
      cur = cur.Append(FILE_PATH_LITERAL("Logs"));
      break;
      
    case FILE_LUNETIX_EXE:
      if (!base::PathService::Get(base::FILE_EXE, &cur))
        return false;
      break;
      
    case FILE_RESOURCES_PACK:
      if (!base::PathService::Get(base::DIR_MODULE, &cur))
        return false;
      cur = cur.Append(FILE_PATH_LITERAL("lunetix.pak"));
      break;
      
    default:
      return false;
  }
  
  *result = cur;
  return true;
}

}  // namespace

void RegisterPathProvider() {
  base::PathService::RegisterProvider(PathProvider, PATH_START, PATH_END);
}

}  // namespace lunetix