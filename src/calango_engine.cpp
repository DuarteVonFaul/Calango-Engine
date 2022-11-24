
#include <calango/calango_engine.h>
#include <stdio.h>

namespace calango
{
  Engine::Engine()
  {
    printf("engine strted\n");
  }

  Engine::~Engine()
  {
    printf("engine terminated\n");
  }
}
