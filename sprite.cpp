// Character Sprite
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Sprite
{
  public:
    // constructor
    Sprite();
    
    // destructor
    ~Sprite();

    // load image from path
    bool loadFromFile( string path);

    // deallocate sprite
    void free();

    // render sprite at point
    void render( int x, int y, SDL_Rect *clip = NULL );

    // get sprite dimensions
    int getWidth();
    int getHeight();
  
  private:
    SDL_Texture *sprite;

    // image dimensions
    int width;
    int height;
};

// load media
bool loadMedia();

// main window and event
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

// sprites
Sprite sheet;
SDL_Rect spriteClips[ 1 ];

Sprite::Sprite()
{
  sprite = NULL;
  width = 0;
  height = 0;
}

Sprite::~Sprite()
{
  free();
}

bool Sprite::loadFromFile( string path )
{
  free();

  // the final sprite
  SDL_Texture *newSprite = NULL;

  // load image from path
  SDL_Surface *loadedSprite = IMG_Load( path.c_str() );
  if ( loadedSprite == NULL )
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  }
  else
  {
    //Color key image
    // SDL_SetColorKey( loadedSprite, SDL_TRUE, SDL_MapRGB( loadedSprite->format, 0, 0xFF, 0xFF )

    // create sprite from surface
    newSprite = SDL_CreateTextureFromSurface( renderer, loadedSprite );
    if( newSprite == NULL )
    {
      printf( "Unable to create sprite from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    // free surface
    SDL_FreeSurface( loadedSprite );
  }
  
  sprite = newSprite;
  return sprite != NULL;
}

void Sprite::free()
{
  if ( sprite != NULL )
  {
    SDL_DestroyTexture( sprite );
    sprite = NULL;
    width = 0;
    height = 0;
  }
}

void Sprite::render( int x, int y, SDL_Rect *clip )
{
  // set rendering rect and render to screen
  SDL_Rect dstrect = { x, y, width, height };

  if( clip != NULL )
  {
    dstrect.w = clip->w;
    dstrect.h = clip->h;
  }

  SDL_RenderCopy( renderer, sprite, clip, &dstrect );
}

int Sprite::getWidth()
{
  return width;
}

int Sprite::getHeight()
{
  return height;
}

bool loadMedia()
{
  bool success = true;

  // load sheet
  if( !sheet.loadFromFile( "img/hyptosis_sprites-and-tiles-for-you.png" ) )
  {
      printf( "Failed to load sprite sheet!\n" );
      success = false;
  }
  else
  {
    // valkyrie
    spriteClips[0].x = 659;
    spriteClips[0].y = 305;
    spriteClips[0].w = 32;
    spriteClips[0].h = 45;
  }

  return success;
}

void close()
{
  sheet.free();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = NULL;
  renderer = NULL;

  IMG_Quit();
  SDL_Quit();
}

int main()
{
  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_INIT_GAMECONTROLLER) < 0)
  {
    printf("SDL_Init failed: %s\n", SDL_GetError());
  }

  // create window and renderer
  if (SDL_CreateWindowAndRenderer( WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP, &window, &renderer)) 
  {
      printf("Couldn't create window and renderer: %s\n", SDL_GetError());
  }

  bool quit = false;

  while(!quit)
  {
    while( SDL_PollEvent(&event) )
    {
      switch (event.type)
      {
      case SDL_QUIT:
        quit = 1;
        break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    // SDL_RenderClear(renderer);

    // sheet.render( WINDOW_WIDTH - spriteClips[0].w / 2, WINDOW_HEIGHT - spriteClips[0].h / 2, &spriteClips[0] );
    sheet.render( 0, 0, &spriteClips[0] );
    SDL_RenderPresent( renderer );
  }

  close();

  return 0;
}
