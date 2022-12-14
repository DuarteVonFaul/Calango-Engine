#ifndef CALANGO_ENGINE
#define CALANGO_ENGINE

#include <calango/calango_platform.h>

#ifdef CALANGO_PLATFORM_WINDOWS
#ifdef CALANGO_ENGINE_IMPLEMENTATION
#define CALANGO_ENGINE_API __declspec(dllexport)
#else
#define CALANGO_ENGINE_API __declspec(dllimport)
#endif //CALANGO_ENGINE_IMPLEMENTATION
#else
#define CALANGO_ENGINE_API
#endif // CALANGO_PLATFORM_WINDOWS

namespace calango
{
  struct CALANGO_ENGINE_API Engine final
  {
    Platform platform;

    Engine();
    ~Engine();
  };
}

#endif  //CALANGO_ENGINE
