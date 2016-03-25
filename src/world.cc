#include "world.h"

#include <algorithm>

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

void World::addEnemy(std::unique_ptr<Enemy> enemy)
{
    enemies.push_back(move(enemy));
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
    updateObjects();
    resolveCollisions();
}

void World::updateObjects()
{
    player.update(laser_manager);
    auto player_pos = player.getPos();

    for (auto& enemy : enemies) {
        enemy->update(player_pos, laser_manager);
    }

    auto& enemy_lasers = laser_manager.getEnemyLasers();
    for (auto& laser : enemy_lasers) {
        laser->update();
    }
    
    auto& player_lasers = laser_manager.getPlayerLasers();
    for (auto& laser : player_lasers) {
        laser->update();
    }
}

void World::resolveCollisions()
{
    auto player_hitbox = player.getAABB();
    
    bool player_collides = std::any_of(begin(enemies), end(enemies),
                                       [&player_hitbox] (auto& enemy)
                                       {return enemy->collides(player_hitbox);});

    const auto& enemy_lasers = laser_manager.getEnemyLasers();
    bool player_hit = std::any_of(begin(enemy_lasers), end(enemy_lasers),
                                  [&player_hitbox] (auto& laser)
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

    enemies.erase(std::remove_if(begin(enemies), end(enemies),
                                 [] (auto& e) { return e->isDead(); }),
                  end(enemies));

    laser_manager.removeDeadLasers();
}
