#include "game.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>

#include "assets.h"
#include "constants.h"
#include "state_manager.h"
#include "music_manager.h"

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

void Game::freeLoadedAssets() const
{
    Assets::destroyInstance();
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
    StateManager state(renderer);
    MusicManager music;
    music.start();

    while (state.stillPlaying())
    {
	auto frame_start_time = SDL_GetTicks();
	state.update();
	music.update(state.getCurrent());
	auto frame_end_time = SDL_GetTicks();

	sleepIfFrameTooFast(frame_start_time, frame_end_time);
    }
}

void Game::sleepIfFrameTooFast(Uint32 start, Uint32 end) const
{
    // Duration in ms
    const int INTENDED_DURATION = 17;
    Uint32 time_elapsed = end - start;

    if (time_elapsed < INTENDED_DURATION)
    {
	SDL_Delay(INTENDED_DURATION - time_elapsed);
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

void Game::loadAssets() const
{
    auto& assets = Assets::getInstance();

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

    assets.loadMusic("menu", "sounds/menu_music.mp3");
    assets.loadMusic("play", "sounds/play_music.mp3");
}
