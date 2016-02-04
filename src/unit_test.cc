#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../inc/player.h"
#include "../inc/asset_manager.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

bool initSDL() 
{
    bool success{true};

    if ( SDL_Init(SDL_INIT_VIDEO) != 0 || SDL_Init(SDL_INIT_AUDIO) != 0 ) 
    {
        cerr << "Error initializing SDL" << endl;
        success = false;
    }
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
    {
        cerr << "Error initializing SDL_Mixer" << endl;
        success = false;
    }    
    if ( IMG_Init(0) != 0 ) 
    {
        cerr << "Error initializing SDL_Image" << endl; 
        success = false;
    }
    if ( TTF_Init() != 0 ) 
    {
        cerr << "error initializing ttf_init" << endl;
        success = false;
    }

    return success;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void run()
{
    const int SCREEN_WIDTH {1024};
    const int SCREEN_HEIGHT {768};

    window = SDL_CreateWindow("SPACECRAZE", SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                              SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    Player player{400, 400};
    SDL_RenderCopy(renderer, AssetManager::getInstance().getTexture("background")->getTexture(), NULL, NULL);
    
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);
}

void loadMedia() 
{
    AssetManager::getInstance().loadTexture("asteroid", 
                                               "../sprites/meteor.png",
                                               1, renderer);
    AssetManager::getInstance().loadTexture("background", 
                                               "../sprites/background.jpg", 
                                               1, renderer);
    AssetManager::getInstance().loadTexture("blaster", 
                                               "../sprites/blaster.png", 
                                               1, renderer);
    AssetManager::getInstance().loadTexture("drone", 
                                               "../sprites/drone.png", 
                                               0.5, renderer);
    AssetManager::getInstance().loadTexture("player", 
                                               "../sprites/playership.png",
                                               0.60, renderer);
    AssetManager::getInstance().loadTexture("laser_friendly", 
                                               "../sprites/playerlaser.png", 
                                               1, renderer);
    AssetManager::getInstance().loadTexture("laser_hostile", 
                                               "../sprites/enemylaser.png", 
                                               1, renderer);
    AssetManager::getInstance().loadTexture("singularity", 
                                               "../sprites/singularity.png", 
                                               1, renderer);

    AssetManager::getInstance().loadMusic("menu", "../sounds/menu_music.mp3");
    AssetManager::getInstance().loadMusic("play", "../sounds/play_music.mp3");

    AssetManager::getInstance().loadFont("button", "../fonts/Akashi.ttf", 36);
}

int main()
{
    if (initSDL()) 
    {
        try
        {
            loadMedia();
            run();
        }
        catch(string& e)
        {
            cerr << e << endl;
        }
    }
    else 
    {
        cerr << "Exiting!" << endl;
    }

    
    close();

    return 0;
}
