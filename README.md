# SDL Intro

## Download, Build and Install SDL

Download latest source from [https://www.libsdl.org/download-2.0.php](https://www.libsdl.org/download-2.0.php)

```
mkdir sdl-dev
cd sdl-dev
tar -xzf ~/Downloads/SDL2-2.0.12.tar.gz -C .
cd SDL2-2.0.12
mkdir build
cd build
../configure
make
sudo make install
```

## Setup and Compilation

```
mkdir sdl-intro
cd sdl-intro
touch intro.c # paste in code below
gcc -o bin/intro.out intro.c `sdl2-config --cflags --libs` -lSDL2_image && ./bin/intro.out
./bin/intro.out
```

## Basic SDL_Init() intro.c

```
#include "SDL2/SDL.h"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_INIT_GAMECONTROLLER) < 0) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    /* ... */

    SDL_Quit();

    return 0;
}
```