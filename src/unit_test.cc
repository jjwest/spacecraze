#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../inc/player.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

bool initSDL() 
{
    bool success{true};

    if ( SDL_Init(SDL_INIT_VIDEO) != 0 || SDL_Init(SDL_INIT_AUDIO) != 0 ) {
        cerr << "Error initializing SDL" << endl;
        success = false;
    }
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        cerr << "Error initializing SDL_Mixer" << endl;
        success = false;
    }    
    if ( IMG_Init(0) != 0 ) {
        cerr << "Error initializing SDL_Image" << endl; 
        success = false;
    }
    if ( TTF_Init() != 0 ) {
        cerr << "error initializing ttf_init" << endl;
        success = false;
    }

    return success;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
int main()
{
    if (!initSDL()) {
        cerr << "Exiting!" << endl;
        return 0;
    }

    const int SCREEN_WIDTH{1024};
    const int SCREEN_HEIGHT{768};

    window = SDL_CreateWindow("SPACECRAZE", SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                              SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    Player player{400, 400, renderer};
    player.draw(renderer);

    SDL_Delay(3000);
    close();

    return 0;
}
