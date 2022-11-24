
#include <calango/calango.h>
#include <calango/calango_platform.h>
#include <calango/calango_engine.h>

namespace calango
{
  namespace launcher
  {
    int calangoMain(int argc, char** argv)
    {
      calango::Engine engine;
      engine.platform.showMessage("Hello calango engine!");
      return 0;
    }
  }
}

// Windows program entrypoint
#ifdef CALANGO_PLATFORM_WINDOWS
#include "win64\calango_resource_win64.h"
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  //TODO(marcio) handle command line here
  
  return calango::launcher::calangoMain(0, (char**) lpCmdLine);
}

#endif  // CALANGO_PLATFORM_WINDOWS

