#include "world.h"

#include <algorithm>
#include <numeric>

#include "point.h"
#include "constants.h"
#include "asset_manager.h"
#include "enums.h"

World::World(SDL_Renderer* renderer)
    : player{ {500, 350} },
      user_interface{renderer}{}

bool World::playerIsDead() const
{
    return player.isDead();
}

int World::getScore() const
{
    return score;
}

void World::update()
{
    usePlayerSpecial();
    updateObjects();
    resolveCollisions();
    updateScore();
    removeDeadObjects();
}

void World::addEnemy(std::unique_ptr<Enemy> enemy)
{
    enemies.push_back(move(enemy));
}

bool rightMouseButtonPressed()
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

void World::usePlayerSpecial()
{
    if (rightMouseButtonPressed() && player.hasSpecial()) {
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

    auto draw = [&renderer](auto& obj) { obj->draw(renderer); };
    std::for_each(begin(enemies), end(enemies), draw);
    
    auto& enemy_lasers = laser_manager.getEnemyLasers();
    std::for_each(begin(enemy_lasers), end(enemy_lasers), draw);
    
    auto& player_lasers = laser_manager.getPlayerLasers();
    std::for_each(begin(player_lasers), end(player_lasers), draw);

    user_interface.draw(renderer, score, player.hasSpecial());
    player.draw(renderer);
    SDL_RenderPresent(renderer);
}

void World::updateObjects()
{
    player.update(laser_manager);

    auto player_pos = player.getPos();
    for (auto& enemy : enemies) {
        enemy->update(player_pos, laser_manager);
    }

    laser_manager.updateLasers();
}

void World::updateScore()
{
    for (const auto& enemy : enemies) {
        if (enemy->isDead()) {
            score += enemy->getScore();
        }
    }
}

void World::resolveCollisions()
{
    AABB player_hitbox = player.getHitbox();
    const auto& enemy_lasers = laser_manager.getEnemyLasers();
    bool player_hit = std::any_of(begin(enemy_lasers), end(enemy_lasers),
				  [&player_hitbox] (auto& laser)
				  { return laser->collides(player_hitbox); });

    bool player_collides = std::any_of(begin(enemies), end(enemies),
				       [&player_hitbox] (auto& enemy)
				       { return enemy->collides(player_hitbox); });

    if (player_collides || player_hit) {
        player.reduceHealth(999);
    }

    const auto& player_lasers = laser_manager.getPlayerLasers();
    for (auto& laser : player_lasers) {
        for (auto& enemy : enemies) {
            if (laser->collides(enemy->getHitbox())) {
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
