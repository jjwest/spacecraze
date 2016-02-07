#include "../inc/game.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../inc/asset_manager.h"
#include "../inc/enums.h"
#include "../inc/constants.h"
#include "../inc/player.h"

Game::Game() : window{nullptr}, renderer{nullptr} 
{
    initSDL();
    loadMedia();
}

Game::~Game()  
{
    AssetManager::destroyInstance();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::run() 
{


}

void Game::initSDL() 
{
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 || SDL_Init(SDL_INIT_AUDIO) != 0 ) 
    {
        throw "Error initializing SDL";
    }
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
    {
        throw "Error initializing SDL_Mixer";
    }    
    if ( IMG_Init(0) != 0 ) 
    {
        throw "Error initializing SDL_Image";
    }
    if ( TTF_Init() != 0 ) 
    {
        throw "Error initializing ttf_init";
    }

    window = SDL_CreateWindow("SPACECRAZE", SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                                          SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::selectMusic() {}


void Game::loadMedia() 
{
    auto& assets = AssetManager::getInstance();

    assets.loadTexture("asteroid", "../sprites/meteor.png", 1, renderer);
    assets.loadTexture("background", "../sprites/background.jpg", 1, renderer);
    assets.loadTexture("blaster", "../sprites/blaster.png", 1, renderer);
    assets.loadTexture("drone", "../sprites/drone.png", 0.5, renderer);
    assets.loadTexture("player", "../sprites/playership.png", 0.60, renderer);
    assets.loadTexture("laser_friendly", "../sprites/playerlaser.png", 1, renderer);
    assets.loadTexture("laser_hostile", "../sprites/enemylaser.png", 1, renderer);
    assets.loadTexture("singularity", "../sprites/singularity.png", 1, renderer);

    assets.loadMusic("menu", "../sounds/menu_music.mp3");
    assets.loadMusic("play", "../sounds/play_music.mp3");

    assets.loadFont("button", "../fonts/Akashi.ttf", 36);
}

