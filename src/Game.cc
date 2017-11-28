#include "Game.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>

#include "AssetManager.h"
#include "Constants.h"
#include "EnterHighscore.h"
#include "Menu.h"
#include "MusicManager.h"
#include "Options.h"
#include "Play.h"
#include "ViewHighscore.h"

Game::Game()
{
    initSDL();
    createWindowAndRenderer();
    loadAssets();
}

Game::~Game()
{
    AssetManager::destroyInstance();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    shutdownSDL();
}

void Game::shutdownSDL() const
{
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::run()
{
    MusicManager music;
    music.start();
    current_state.reset(new Menu());

    while (running)
    {
		auto frame_start_time = SDL_GetTicks();
		current_state->handleEvents();
		current_state->update();
		current_state->draw(renderer);
		music.update(current_state_id);
		auto next_state = current_state->getNextState();

		changeStateIfRequired(next_state);
		auto frame_end_time = SDL_GetTicks();
		sleepIfFrameTooFast(frame_start_time, frame_end_time);
    }
}

void Game::changeStateIfRequired(State next_state)
{
    if (next_state != current_state_id)
    {
        switch (next_state)
		{
        case State::PLAY:
		{
            current_state.reset(new Play(renderer, score));
            break;
		}
        case State::MENU:
		{
			current_state.reset(new Menu());
			break;
		}
		case State::OPTIONS:
		{
			current_state.reset(new Options());
			break;
		}
        case State::VIEW_HIGHSCORE:
		{
			current_state.reset(new ViewHighscore(score.get()));
			break;
		}
		case State::ENTER_HIGHSCORE:
		{
			current_state.reset(new EnterHighscore(score));
			break;
		}
		case State::QUIT:
		{
			running = false;
			break;
		}
		}
    }
    current_state_id = next_state;
}

void Game::sleepIfFrameTooFast(Uint32 start, Uint32 end) const
{
    const Uint32 INTENDED_DURATION_MS = 10;
    auto time_elapsed = end - start;

    if (time_elapsed < INTENDED_DURATION_MS)
    {
		SDL_Delay(INTENDED_DURATION_MS - time_elapsed);
    }
}

void Game::initSDL() const
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
    window = SDL_CreateWindow(
		"SPACECRAZE",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
		);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void Game::loadAssets() const
{
    auto& assets = AssetManager::instance();

    assets.loadTexture("asteroid", "meteor.png", renderer);
    assets.loadTexture("background", "background.jpg", renderer);
    assets.loadTexture("blaster", "blaster.png", renderer);
    assets.loadTexture("drone", "drone.png", renderer);
    assets.loadTexture("player", "playership.png", renderer);
    assets.loadTexture("player_laser", "playerlaser.png", renderer);
    assets.loadTexture("enemy_laser", "enemylaser.png", renderer);
    assets.loadTexture("singularity", "singularity.png", renderer);
    assets.loadTexture("doubledamage", "double_damage.png", renderer);

    assets.loadFont("text", "Akashi.ttf", 36);
    assets.loadFont("title", "Akashi.ttf", 60);

    assets.loadMusic("menu", "menu_music.mp3");
    assets.loadMusic("play", "play_music.mp3");

    assets.loadSoundEffect("small_laser", "small_laser.wav");
    assets.loadSoundEffect("big_laser", "big_laser.wav");
}
