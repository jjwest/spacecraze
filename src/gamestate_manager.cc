#include "../inc/gamestate_manager.h"

GamestateManager::GamestateManager(SDL_Renderer* renderer)
    : gamestate{menu} {}

GamestateManager::~GamestateManager()  {
    for (auto it : game) {
        delete it;
    }
}

GameStates GamestateManager::update() {
    switch ( gamestate ) {
    case MENU:
        gamestate = menu.update()
        break;
            
    case PLAY:
        if ( noActiveGame() ) {
            startNewGame();
            gamestate = updateGame();
        }
        else {
            gamestate = updateGame();
        }
        break;

    case HIGHSCORE:
        break;
    }

    return gamestate;
}

bool GamestateManager::noActiveGame() {
    return game.empty();
}

void GamestateManager::startNewGame() {
    game.push_back(new PlayState(renderer))
}

GameStates GamestateManager::updateGame() {
    return game.at(0).update();
}
