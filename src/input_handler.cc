#include "../inc/input_handler.h"

using namespace std;

InputHandler::InputHandler() : event{} {}

GameStates InputHandler::update(GameStates gamestate)
{
    return gamestate;
}

GameStates InputHandler::update(GameStates gamestate, 
                                map<string, bool>& player_actions)
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type) 
        {
        case SDL_QUIT:
            gamestate = QUIT;
            break;

        case SDL_KEYDOWN:
            handleKeyPressed(player_actions);
            break;

        case SDL_KEYUP:
            handleKeyReleased(player_actions);
            break;

        case SDL_MOUSEBUTTONDOWN:
            handleMousePressed(player_actions);
            break;

        case SDL_MOUSEBUTTONUP:
            handleMouseReleased(player_actions);
            break;
        }
    }

    return gamestate;   
}

void InputHandler::handleKeyPressed(map<string, bool>& player_actions)
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

void InputHandler::handleKeyReleased(map<string, bool>& player_actions)
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

void InputHandler::handleMousePressed(map<string, bool>& player_actions)
{
    switch (event.button.button) 
    {
    case SDL_BUTTON_LEFT:
        player_actions["SHOOT"] = true;
        break;

    case SDL_BUTTON_RIGHT:
        player_actions["SINGULARITY"] = true;
        break;
    }
}

void InputHandler::handleMouseReleased(map<string, bool>& player_actions)
{
    switch (event.button.button) 
    {
    case SDL_BUTTON_LEFT:
        player_actions["SHOOT"] = false;
        break;

    case SDL_BUTTON_RIGHT:
        player_actions["SINGULARITY"] = false;
        break;
    }
}
