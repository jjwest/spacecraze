#include "game.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

#include "asset_manager.h"
#include "enums.h"
#include "constants.h"
#include "play.h"
#include "menu.h"

Game::Game()
    : window{nullptr}, renderer{nullptr}, current_state_id{PLAY}
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
    GameStates next_state_id;
    current_state.reset(new Menu(renderer));
    
    while (current_state_id != QUIT) {
        current_state->handleEvents();
        current_state->update();
        current_state->render(renderer);
        next_state_id = current_state->getNextState();
        changeState(next_state_id);
        SDL_Delay(10);
    }
}

void Game::initSDL() 
{
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 || SDL_Init(SDL_INIT_AUDIO) != 0 )  {
        throw std::runtime_error("Error initializing SDL");
    }
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        throw std::runtime_error("Error initializing SDL_Mixer");
    }    
    if ( IMG_Init(0) != 0 ) {
        throw std::runtime_error("Error initializing SDL_Image");
    }
    if ( TTF_Init() != 0 ) {
        throw std::runtime_error("Error initializing TTF_init");
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

    assets.loadTexture("asteroid", "sprites/meteor.png", 1, renderer);
    assets.loadTexture("background", "sprites/background.jpg", 1, renderer);
    assets.loadTexture("blaster", "sprites/blaster.png", 1, renderer);
    assets.loadTexture("drone", "sprites/drone.png", 0.5, renderer);
    assets.loadTexture("player", "sprites/playership.png", 0.60, renderer);
    assets.loadTexture("player_laser", "sprites/playerlaser.png", 0.5, renderer);
    assets.loadTexture("enemy_laser", "sprites/enemylaser.png", 0.75, renderer);
    assets.loadTexture("singularity", "sprites/singularity.png", 1, renderer);

    assets.loadMusic("menu", "sounds/menu_music.mp3");
    assets.loadMusic("play", "sounds/play_music.mp3");

    assets.loadFont("button", "fonts/Akashi.ttf", 36);
}

void Game::changeState(GameStates next_state_id)
{
    if (next_state_id != current_state_id) {
        switch (next_state_id) {
        case PLAY:
            current_state.reset(new Play());
            break;

        case MENU:
            current_state.reset(new Menu(renderer));
            break;

        case HIGHSCORE:
            break;

        case QUIT:
            break;
        }
        
        current_state_id = next_state_id;
    }
}
