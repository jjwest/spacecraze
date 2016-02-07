#include "../include/world.h"

#include "../include/aabb.h"
#include "../include/resourcemanager.h"

using namespace std;

namespace {
    void drawBackground(SDL_Renderer* renderer, SDL_Texture* texture) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    }
}

World::World() : 
    player{ResourceManager::getInstance().getTexture("player"), 500, 350, 3, 1},
    background{ResourceManager::getInstance().getTexture("background")->getTexture()}
    {}

World::~World() {
    for (auto i : asteroids) {
        delete i;
    }
    for (auto i : blasters) {
        delete i;
    }
    for (auto i : drones) {
        delete i;
    }
    for (auto i : friendly_lasers) {
        delete i;
    }
    for (auto i : hostile_lasers) {
        delete i;
    }
}

GameStates World::update(SDL_Renderer* renderer, 
                         const map<string, bool>& player_actions) {
    GameStates gamestate{ PLAY };
    draw(renderer);
    player_actions.at(0);
    return gamestate;
}

void World::addEnemyAsteroid() {}

void World::addEnemyBlaster() {}

void World::addEnemyDrone() {}

void World::addFriendlyLaser() {}

void World::addHostileLaser() {}

void World::draw(SDL_Renderer* renderer) {
    drawBackground(renderer, background);

    for (auto i : asteroids) {
        i->draw(renderer);
    }
    for (auto i : blasters) {
        i->draw(renderer);
    }
    for (auto i : drones) {
        i->draw(renderer);
    }
    for (auto i : friendly_lasers) {
        i->draw(renderer);
    }
    for (auto i : hostile_lasers) {
        i->draw(renderer);
    }

    player.draw(renderer); 
}


