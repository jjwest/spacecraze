#include "../inc/game.h"

#include <SDL2/SDL_ttf.h>

#include "../inc/gamestate_manager.h"
#include "../inc/globals.h"

Game::Game() : {nullptr}, renderer{nullptr} {
    initializeSDL();
    loadMedia();
}

Game::~Game()  {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::run() {
    GameStates gamestate{ MENU };
    GamestateManager gamestate_manager(renderer);
    bool running{true};

    while ( running ) {
        gamestate = gamestate_manager.update();
        if ( gamestate == QUIT ) {
            running = false;
        }
    }
}

void Game::initializeSDL() {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 || SDL_Init(SDL_INIT_AUDIO) != 0 ) {
        std::cerr << "Error initializing SDL" << std::endl;
        exit(1);
    }
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        std::cerr << "Error initializing SDL_Mixer" << std::endl;
        exit(1);
    }    
    if ( IMG_Init(0) != 0 ) {
        std::cerr << "Error initializing SDL_Image" << std::endl;
        exit(1);
    }
    if ( TTF_Init() != 0 ) {
        std::cerr << "error initializing ttf_init" << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("SPACECRAZE", SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                                          SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::selectMusic() {}


void Game::loadMedia() {
    ResourceManager::getInstance().loadTexture("asteroid", 
                                               "../sprites/meteorBrown_big3.png",
                                               1, renderer);
    ResourceManager::getInstance().loadTexture("background", 
                                               "../sprites/background.jpg", 
                                               1, renderer);
    ResourceManager::getInstance().loadTexture("blaster", 
                                               "../sprites/enemyRed1.png", 
                                               1, renderer);
    ResourceManager::getInstance().loadTexture("drone", 
                                               "../sprites/enemyRed2.png", 
                                               0.5, renderer);
    ResourceManager::getInstance().loadTexture("player", 
                                               "../sprites/playerShip2_green.png",
                                               0.60, renderer);
    ResourceManager::getInstance().loadTexture("laser_friendly", 
                                               "../sprites/laserGreen11.png", 
                                               1, renderer);
    ResourceManager::getInstance().loadTexture("laser_hostile", 
                                               "../sprites/laserRed16.png", 
                                               1, renderer);
    ResourceManager::getInstance().loadTexture("singularity", 
                                               "../sprites/laserGree.png", 
                                               1, renderer);

    ResourceManager::getInstance().loadMusic("menu", "../sounds/menu_music.mp3");
    ResourceManager::getInstance().loadMusic("play", "../sounds/play_music.mp3");

    ResourceManager::getInstance().loadFont("button", "../fonts/Akashi.ttf", 36);
}

