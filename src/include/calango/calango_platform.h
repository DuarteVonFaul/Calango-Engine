#ifndef CALANGO_PLATFORM_H
#define CALANGO_PLATFORM_H

#ifdef _WIN32
  #include <windows.h>
  #define CALANGO_PLATFORM_WINDOWS
 #else
  #define CALANGO_PLATFORM_UNKNOWN
  #error "Unsuported platform"
#endif

#ifdef CALANGO_PLATFORM_WINDOWS
#ifdef CALANGO_PLATFORM_IMPLEMENTATION
#define CALANGO_PLATFORM_API __declspec(dllexport)
#else
#define CALANGO_PLATFORM_API __declspec(dllimport)
#endif //CALANGO_PLATFORM_IMPLEMENTATION
#else
#define CALANGO_PLATFORM_API
#endif // CALANGO_PLATFORM_WINDOWS

namespace calango
{

  struct Window;

  struct CALANGO_PLATFORM_API Platform final
  {
    void showMessage(char* message);

    Window* createWindow(int width, int height, const char* title);
  };

  

} 

#endif  //CALANGO_PLATFORM_H
