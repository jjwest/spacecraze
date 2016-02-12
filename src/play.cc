#include "../include/play.h"

Play::Play(SDL_Renderer* r)
    : renderer{r}, next_state{PLAY}, player{{500, 350}} {}


void Play::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            next_state = QUIT;
            break;

        case SDL_KEYDOWN:
            handleKeyPressed();
            break;

        case SDL_KEYUP:
            handleKeyReleased();
            break;

        case SDL_MOUSEBUTTONDOWN:
            handleMousePressed();
            break;

        case SDL_MOUSEBUTTONUP:
            handleMouseReleased();
            break;
        }
    }
}

void Play::update()
{
    enemy_generator.update(enemies);
    player.update(player_actions);
    enemies.update(player.getPos(), lasers);
    handleCollisions();
}

void Play::render()
{
    
}

GameStates Play::nextState()
{
    return next_state;
}

void Play::handleCollisions()
{
    enemies.checkCollisions(player);
    enemies.checkCollisions(lasers);
    player.checkCollisions(lasers);
}

void Play::handleKeyPressed()
{
    switch (event.key.keysym.sym)
    {
    case SDLK_w:
        player_actions["UP"] = true;
        break;

    case SDLK_s:
        player_actions["DOWN"] = true;
        break;

    case SDLK_a:
        player_actions["LEFT"] = true;
        break;

    case SDLK_d:
        player_actions["RIGHT"] = true;
        break;
    }
}

void Play::handleKeyReleased()
{
    switch (event.key.keysym.sym)
    {
    case SDLK_w:
        player_actions["UP"] = false;
        break;

    case SDLK_s:
        player_actions["DOWN"] = false;
        break;

    case SDLK_a:
        player_actions["LEFT"] = false;
        break;

    case SDLK_d:
        player_actions["RIGHT"] = false;
        break;
    }
}

void Play::handleMousePressed()
{
    switch (event.button.button)
    {
    case SDL_BUTTON_LEFT:
        player_actions["SHOOT"] = true;
        break;

    case SDL_BUTTON_RIGHT:
        player_actions["SINGULARITY"] = true;
    }
}

void Play::handleMouseReleased()
{
    switch (event.button.button)
    {
    case SDL_BUTTON_LEFT:
        player_actions["SHOOT"] = false;
        break;

    case SDL_BUTTON_RIGHT:
        player_actions["SINGULARITY"] = false;
    }
}
