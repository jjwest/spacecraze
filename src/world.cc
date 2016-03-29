#include "world.h"

#include <algorithm>
#include <numeric>

#include "point.h"
#include "constants.h"
#include "asset_manager.h"
#include "enums.h"


World::World()
    : player{ {500, 350} } {}

bool World::playerIsDead() const
{
    return player.isDead();
}

int World::getScore() const
{
    return score;
}

void World::addEnemy(std::unique_ptr<Enemy> enemy)
{
    enemies.push_back(move(enemy));
}

void World::usePlayerSpecial()
{
    if (player.hasSingularity()) {
        for (const auto& enemy : enemies) {
            enemy->reduceHealth(999);
        }
        
        player.setSpecial(false);
    }
}

void World::render(SDL_Renderer* renderer)
{
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);

    for (const auto& enemy : enemies) {
        enemy->draw(renderer);
    }

    auto& enemy_lasers = laser_manager.getEnemyLasers();
    for (const auto& laser : enemy_lasers) {
        laser->draw(renderer);
    }
    
    auto& player_lasers = laser_manager.getPlayerLasers();
    for (const auto& laser : player_lasers) {
        laser->draw(renderer);
    }

    player.draw(renderer);
    SDL_RenderPresent(renderer);
}

void World::update()
{
    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        usePlayerSpecial();
    }
    updateObjects();
    resolveCollisions();
    updateScore();
    removeDeadObjects();
}

void World::updateObjects()
{
    player.update(laser_manager);
    auto player_pos = player.getPos();

    for (auto& enemy : enemies) {
        enemy->update(player_pos, laser_manager);
    }

    const auto& enemy_lasers = laser_manager.getEnemyLasers();
    for (auto& laser : enemy_lasers) {
        laser->update();
    }
    
    const auto& player_lasers = laser_manager.getPlayerLasers();
    for (auto& laser : player_lasers) {
        laser->update();
    }
}

void World::updateScore()
{
    score = std::accumulate(begin(enemies), end(enemies), score,
                            [](int a, const auto& e) {
                                return e->isDead() ? a += e->getScore() : a;
                            });
    
}

void World::resolveCollisions()
{
    auto player_hitbox = player.getAABB();
    
    bool player_collides = std::any_of(begin(enemies), end(enemies),
                                       [&player_hitbox] (const auto& enemy)
                                       {return enemy->collides(player_hitbox);});

    const auto& enemy_lasers = laser_manager.getEnemyLasers();
    bool player_hit = std::any_of(begin(enemy_lasers), end(enemy_lasers),
                                  [&player_hitbox] (const auto& laser)
                                  { return laser->collides(player_hitbox); });

    if (player_collides || player_hit) {
        player.reduceHealth(999);
    }

    const auto& player_lasers = laser_manager.getPlayerLasers();
    for (auto& laser : player_lasers) {
        for (auto& enemy : enemies) {
            if (laser->collides(enemy->getAABB())) {
                enemy->reduceHealth(laser->getDamage());
                laser->reduceHealth(999);
            }
        }
    }
}

void World::removeDeadObjects()
{
    laser_manager.removeDeadLasers();
    enemies.erase(std::remove_if(begin(enemies), end(enemies),
                                 [](auto& e) { return e->isDead(); }),
                  end(enemies));
}
