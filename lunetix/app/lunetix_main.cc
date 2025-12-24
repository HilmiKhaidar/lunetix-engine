#include "lunetix/app/lunetix_main_delegate.h"

#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/debug/debugger.h"
#include "base/process/memory.h"
#include "base/time/time.h"
#include "build/build_config.h"
#include "content/public/app/content_main.h"

#if BUILDFLAG(IS_WIN)
#include "base/win/win_util.h"
#include "chrome/app/chrome_exe_main_win.h"
#include "chrome/install_static/install_util.h"
#endif

#if BUILDFLAG(IS_WIN)
int APIENTRY wWinMain(HINSTANCE instance,
                      HINSTANCE prev_instance,
                      wchar_t* command_line,
                      int show_command) {
  install_static::InitializeFromPrimaryModule();
  
  lunetix::LunetixMainDelegate delegate(base::TimeTicks::Now());
  content::ContentMainParams params(&delegate);
  params.instance = instance;
  params.sandbox_info = nullptr;
  
  return content::ContentMain(std::move(params));
}
#else
int main(int argc, const char** argv) {
  lunetix::LunetixMainDelegate delegate(base::TimeTicks::Now());
  content::ContentMainParams params(&delegate);
  params.argc = argc;
  params.argv = argv;
  
  return content::ContentMain(std::move(params));
}
#endif