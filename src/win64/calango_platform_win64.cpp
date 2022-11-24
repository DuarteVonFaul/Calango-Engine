
#include <calango/calango_platform.h>
#include <stdio.h>
#include "calango_resource_win64.h"
namespace calango
{

  struct Window
  {
    HANDLE handle;
  };

  void Platform::showMessage(char* message)
  {
      MessageBox(0, message, "calango WIN64 Platform:", 0);
  };

  LRESULT calangoWinProc(
    HWND wRender,
    UINT wMessage,
    WPARAM wParam,
    LPARAM lParam
  )
  {

    return DefWindowProc(wRender, wMessage, wParam, lParam);
  };

  Window* Platform::createWindow(int width, int height, const char* title){

    const char* calangoWinClass = "Calango Window Class";
    WNDCLASSEXA wc = {};
    HINSTANCE hInstance = GetModuleHandleA(NULL);
    

    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = calangoWinProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = calangoWinClass;

    if(!RegisterClassExA(&wc)){
      return nullptr;
    }

    HWND windowHandle = CreateWindowExA(0,
                                        calangoWinClass,
                                        title,
                                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                        CW_USEDEFAULT, 
                                        CW_USEDEFAULT,
                                        width,
                                        height,
                                        NULL,
                                        NULL,
                                        hInstance,
                                        NULL);

    if(!windowHandle){
      return nullptr;
    }

    Window* window = new Window;

    window->handle = windowHandle ; 
    return window;

  };

} 
