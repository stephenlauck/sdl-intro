#include "stdio.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (360)

// speed in pixels/second
#define SPEED (100)
#define BPM (500) // 120 BPM = 1000/2
#define KICK_SOUND "snd/kick.wav"
#define HIHAT_SOUND "snd/hihat.wav"
#define SNARE_SOUND "snd/snare.wav"

Mix_Chunk *kick = NULL;
Mix_Chunk *hihat = NULL;
Mix_Chunk *snare = NULL;

void sdl_info()
{
  SDL_version compiled;
  SDL_version linked;

  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  printf("We compiled against SDL version %d.%d.%d ...\n",
        compiled.major, compiled.minor, compiled.patch);
  printf("But we are linking against SDL version %d.%d.%d.\n",
        linked.major, linked.minor, linked.patch);
  
  const SDL_version *link_version=IMG_Linked_Version();
  SDL_IMAGE_VERSION(&compiled);
  printf("compiled with SDL_image version: %d.%d.%d\n", 
          compiled.major,
          compiled.minor,
          compiled.patch);
  printf("running with SDL_image version: %d.%d.%d\n", 
          link_version->major,
          link_version->minor,
          link_version->patch);
}

void sdl_gamepad()
{
  SDL_GameController *ctrl;
  int i;

  for (i = 0; i < SDL_NumJoysticks(); ++i) {
    if (SDL_IsGameController(i)) {
        char *mapping;
        SDL_Log("Index \'%i\' is a compatible controller, named \'%s\'", i, SDL_GameControllerNameForIndex(i));
        ctrl = SDL_GameControllerOpen(i);
        mapping = SDL_GameControllerMapping(ctrl);
        SDL_Log("Controller %i is mapped as \"%s\".", i, mapping);
        SDL_free(mapping);
    } else {
        SDL_Log("Index \'%i\' is not a compatible controller.", i);
    }
  }
}

void sound_setup( )
{
   // set up sounds
  kick = Mix_LoadWAV(KICK_SOUND);
  if(!kick)
  {
    printf("Mix_LoadWAV: %s\n", Mix_GetError());
    // handle error
  }

  hihat = Mix_LoadWAV( "snd/hihat.wav" );
    if( !hihat )
    {
      printf("Mix_LoadWAV: %s\n", Mix_GetError());
      // handle error
    }

  snare = Mix_LoadWAV( "snd/snare.wav" );
    if( !hihat )
    {
      printf("Mix_LoadWAV: %s\n", Mix_GetError());
      // handle error
    }
}

void play_hihat()
{
  Mix_PlayChannel( -1, hihat, 0 );
}

Uint32 callback( Uint32 interval, void* param )
{
  SDL_Event event;
  SDL_UserEvent userevent;

  /* In this example, our callback pushes a function
  into the queue, and causes our callback to be called again at the
  same interval: */

  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = &play_hihat;
  userevent.data2 = NULL;

  event.type = SDL_USEREVENT;
  event.user = userevent;

  SDL_PushEvent(&event);
  return(interval);
}

int main(int argc, char* argv[])
{
  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_INIT_GAMECONTROLLER) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    return 3;
  }

  if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL Mixer: %s", SDL_GetError());
    return 3;
  }

  // show SDL info
  sdl_info();
  sdl_gamepad();

  // set up sound
  sound_setup();
  SDL_TimerID timerID = SDL_AddTimer( BPM, callback, hihat );
  
  // set up window
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Event event;


  if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
      return 3;
  }

  surface = IMG_Load("img/valkyrie.png");
  if (!surface) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
      return 3;
  }
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
      return 3;
  }
  SDL_FreeSurface(surface);

  // render sprite
  SDL_Rect sprite;

  SDL_QueryTexture(texture, NULL, NULL, &sprite.w, &sprite.h);

  float x_pos = (WINDOW_WIDTH - sprite.w) / 2;
  float y_pos = (WINDOW_HEIGHT - sprite.h) / 2;

  float x_vel = SPEED;
  float y_vel = SPEED;

  // dpad inputs
  int up = 0;
  int down = 0;
  int left = 0;
  int right = 0;

  int quit = 0;

  

  while (!quit) {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_USEREVENT: {
        void (*p) (void*) = event.user.data1;
        p(event.user.data2);
        break;
      }
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYDOWN:
      switch (event.key.keysym.scancode)
      {
      case SDL_SCANCODE_ESCAPE:
        quit = 1;
        break;
      }
      case SDL_CONTROLLERBUTTONDOWN:
        switch ( event.cbutton.button )
        {
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
          up = 1;
          break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
          down = 1;
          break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
          left = 1;
          break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
          right = 1;
          break;
        case SDL_CONTROLLER_BUTTON_A:
          Mix_PlayChannel( -1, kick, 0 );
          break;
        case SDL_CONTROLLER_BUTTON_B:
          Mix_PlayChannel( -1, snare, 0 );
          break;
        }
        break;
      case SDL_CONTROLLERBUTTONUP:
        switch ( event.cbutton.button )
        {
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
          up = 0;
          break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
          down = 0;
          break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
          left = 0;
          break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
          right = 0;
          break;
        break;
        }
      }
    }

    // determine velocity
    x_vel = y_vel = 0;
    if (up && !down) y_vel = -SPEED;
    if (down && !up) y_vel = SPEED;
    if (left && !right) x_vel = -SPEED;
    if (right && !left) x_vel = SPEED;

    // update positions
    x_pos += x_vel / 60;
    y_pos += y_vel / 60;

    // collision detection
    if (x_pos <= 0) x_pos = 0;
    if (y_pos <= 0) y_pos = 0;
    if (x_pos >= WINDOW_WIDTH - sprite.w) x_pos = WINDOW_WIDTH - sprite.w;
    if (y_pos >= WINDOW_HEIGHT - sprite.h) y_pos = WINDOW_HEIGHT - sprite.h;

    // set positions of sprite
    sprite.x = (int) x_pos;
    sprite.y = (int) y_pos;

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    
    sprite.y = (int) y_pos;
    
    SDL_RenderCopy(renderer, texture, NULL, &sprite);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000/60);
  }

  // clean up and exit
  SDL_RemoveTimer( timerID );
  
  Mix_FreeChunk(kick);
  Mix_CloseAudio();

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}