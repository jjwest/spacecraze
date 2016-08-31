#include "game.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stdexcept>

#include "asset_manager.h"
#include "enums.h"
#include "constants.h"
#include "play.h"
#include "menu.h"
#include "enter_highscore.h"
#include "view_highscore.h"

Game::Game()
{
    initSDL();
    createWindowAndRenderer();
    loadAssets();
}

Game::~Game()
{
    freeLoadedAssets();
    destroyWindowAndRenderer();
    shutdownSDL();
}

void Game::freeLoadedAssets()
{
    AssetManager::destroyInstance();
}

void Game::shutdownSDL()
{
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::run()
{
    setStateToMenu();
    current_state_id = State_EnterHighscore;
    current_state.reset(new EnterHighscore(renderer, 1000));

    while (stillPlaying())
    {
	auto frame_start_time = SDL_GetTicks();

        current_state->handleEvents();
        current_state->update();
        current_state->draw(renderer);
        auto next_state = current_state->getNextState();
        changeCurrentStateIfNew(next_state);

	auto frame_end_time = SDL_GetTicks();
	Uint32 time_elapsed = frame_end_time - frame_start_time;
	sleepIfFrameTooFast(time_elapsed);
    }
}


void Game::sleepIfFrameTooFast(Uint32 time_elapsed) const
{
    const int FRAME_INTENDED_DURATION = 10;
    SDL_Delay(FRAME_INTENDED_DURATION - time_elapsed);
}

void Game::setStateToMenu()
{
    current_state.reset(new Menu(renderer));
}

bool Game::stillPlaying() const
{
    return current_state_id != State_Quit;
}

void Game::initSDL()
{
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 || SDL_Init(SDL_INIT_AUDIO) != 0 )
    {
        throw std::runtime_error("Failed to initialize SDL");
    }
    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        throw std::runtime_error("Failed to initialize SDL_Mixer");
    }
    if ( IMG_Init(0) != 0 )
    {
        throw std::runtime_error("Failed to initialize SDL_Image");
    }
    if ( TTF_Init() != 0 )
    {
        throw std::runtime_error("Failed to initialize TTF_init");
    }

}

void Game::createWindowAndRenderer()
{
    window = SDL_CreateWindow("SPACECRAZE", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::destroyWindowAndRenderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::loadAssets()
{
    auto& assets = AssetManager::getInstance();

    assets.loadTexture("asteroid", "sprites/meteor.png", renderer);
    assets.loadTexture("background", "sprites/background.jpg", renderer);
    assets.loadTexture("blaster", "sprites/blaster.png", renderer);
    assets.loadTexture("drone", "sprites/drone.png", renderer);
    assets.loadTexture("player", "sprites/playership.png", renderer);
    assets.loadTexture("player_laser", "sprites/playerlaser.png", renderer);
    assets.loadTexture("enemy_laser", "sprites/enemylaser.png", renderer);
    assets.loadTexture("singularity", "sprites/singularity.png", renderer);

    assets.loadFont("text", "fonts/Akashi.ttf", 36);
    assets.loadFont("title", "fonts/Akashi.ttf", 60);
}

void Game::changeCurrentStateIfNew(States next_state_id)
{
    if (next_state_id != current_state_id)
    {
        switch (next_state_id) {
        case State_Play:
            current_state.reset(new Play(renderer));
            break;

        case State_Menu:
            current_state.reset(new Menu(renderer));
            break;

        case State_ViewHighscore:
	    current_state.reset(new ViewHighscore(renderer));
            break;

	case State_EnterHighscore:
	    current_state.reset(new EnterHighscore(renderer, 0));
	    break;

        case State_Quit:
            break;
        }

    }
    current_state_id = next_state_id;
}
