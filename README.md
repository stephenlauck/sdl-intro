# SDL Intro

## Download, Build and Install SDL

Download latest source from [https://www.libsdl.org/download-2.0.php]

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
gcc -o bin/intro.out intro.c `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_mixer && ./bin/intro.out
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

### Author

* Stephen Lauck ([stephen.lauck@gmail.com](mailto:stephen.lauck@gmail.com))

### Credits

* Thomas Lively's great CS50 video [https://www.youtube.com/watch?v=yFLa3ln16w0](https://www.youtube.com/watch?v=yFLa3ln16w0)

* Sprite Art [https://opengameart.org/content/lots-of-free-2d-tiles-and-sprites-by-hyptosis](https://opengameart.org/content/lots-of-free-2d-tiles-and-sprites-by-hyptosis)