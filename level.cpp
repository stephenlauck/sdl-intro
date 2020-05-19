#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define win_width 640
#define win_height 480
#define fps 60
#define tpf 1000 / fps

int main()
{
  // variables
  SDL_Window *window;
  SDL_Event event;

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    cout << "Error initializing SDL: " << SDL_GetError() << endl;
  }

  // create window
  window = SDL_CreateWindow(
      "Level 1",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      win_width,
      win_height,
      SDL_WINDOW_ALWAYS_ON_TOP
  );

  if (window == NULL)
  {
    cout << "Coult not create window: " << SDL_GetError() << endl;
  }

  // set main loop exit bool
  bool running = true;
  Uint32 last = 0, cur;

  // main loop
  while (running) {
    
    // get cur ticks
    cur = SDL_GetTicks();
    
    while (SDL_PollEvent(&event)) {
      switch (event.type)
      {
        case SDL_QUIT:
          running = false;
          break;
      }
    }

    
    SDL_Delay(floor(tpf - ))
    
  }

  // clean up
  SDL_DestroyWindow( window );
  SDL_Quit();
  
  return 0;
}