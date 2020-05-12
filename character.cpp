#include <SDL2/SDL.h>
#include <SDL2/SDL_image>
#include <SDL2/SDL_mixer>

using namespace std;

int main()
{
 if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_INIT_GAMECONTROLLER) != 0)
  {
    printf("Error initializing SDL: %s\n", SDL_GetError());
  }
}