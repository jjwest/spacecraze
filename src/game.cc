#include "../inc/game.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../inc/asset_manager.h"
#include "../inc/enums.h"
#include "../inc/constants.h"

Game::Game() : window{nullptr}, renderer{nullptr} 
{
    initializeSDL();
    loadMedia();
}

Game::~Game()  
{
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::run() 
{
    // GameStates gamestate{ MENU };
    bool running{true};

    while (running) 
    {
    }
}

void Game::initializeSDL() 
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
    AssetManager::getInstance().loadTexture("asteroid", 
                                               "../sprites/meteorBrown_big3.png",
                                               1, renderer);
    AssetManager::getInstance().loadTexture("background", 
                                               "../sprites/background.jpg", 
                                               1, renderer);
    AssetManager::getInstance().loadTexture("blaster", 
                                               "../sprites/enemyRed1.png", 
                                               1, renderer);
    AssetManager::getInstance().loadTexture("drone", 
                                               "../sprites/enemyRed2.png", 
                                               0.5, renderer);
    AssetManager::getInstance().loadTexture("player", 
                                               "../sprites/playerShip2_green.png",
                                               0.60, renderer);
    AssetManager::getInstance().loadTexture("laser_friendly", 
                                               "../sprites/laserGreen11.png", 
                                               1, renderer);
    AssetManager::getInstance().loadTexture("laser_hostile", 
                                               "../sprites/laserRed16.png", 
                                               1, renderer);
    AssetManager::getInstance().loadTexture("singularity", 
                                               "../sprites/laserGree.png", 
                                               1, renderer);

    AssetManager::getInstance().loadMusic("menu", "../sounds/menu_music.mp3");
    AssetManager::getInstance().loadMusic("play", "../sounds/play_music.mp3");

    AssetManager::getInstance().loadFont("button", "../fonts/Akashi.ttf", 36);
}

