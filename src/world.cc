#include "../include/world.h"

#include <random>
#include <algorithm>

#include "../include/point.h"
#include "../include/constants.h"
#include "../include/asset_manager.h"
#include "../include/enums.h"



World::World() : player{{500, 350}} {}

void World::addEnemyLaser(const Point& pos)
{}

void World::addPlayerLaser(const Point& pos)
{}

void World::addEnemy(std::unique_ptr<Enemy> enemy)
{
    enemies.push_back(move(enemy));
}

void World::render(SDL_Renderer* renderer)
{
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    
    for (auto& enemy : enemies) 
    {
        enemy->draw(renderer);
    }
    for (auto& laser : enemy_lasers) 
    {
        laser->draw(renderer);
    }
    for (auto& laser : player_lasers) 
    {
        laser->draw(renderer);
    }

    player.draw(renderer);
    SDL_RenderPresent(renderer);
}

void World::update()
{}
void World::handleCollisions()
{}

void World::updateObjects()
{
}


