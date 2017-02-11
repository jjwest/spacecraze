#include "World.h"

#include <algorithm>
#include <numeric>

#include "Point.h"
#include "Constants.h"
#include "AssetManager.h"
#include "Enums.h"
#include "ObjectFactory.h"

World::World()
    : player {SDL_Rect {
		  500,
		  350,
		  static_cast<int>(AssetManager::getInstance().getTexture("player")->getWidth() * 0.5),
		  static_cast<int>(AssetManager::getInstance().getTexture("player")->getHeight() * 0.5) }} {}

WorldState World::getState() const
{
    return state;
}

void World::addEnemy(std::unique_ptr<Enemy> enemy)
{
    enemies.push_back(move(enemy));
}

void World::addEnemyLaser(const Point& origin, const Point& destination, double damage)
{
    auto& factory = ObjectFactory::getInstance();
    enemy_lasers.push_back(factory.createEnemyLaser(origin, destination, damage));
}

void World::addPlayerLaser(const Point& origin, double damage)
{
    Point target;
    SDL_GetMouseState(&target.x, &target.y);

    auto& factory = ObjectFactory::getInstance();
    player_lasers.push_back(factory.createPlayerLaser(origin, target, damage));
}

void World::clearEnemies()
{
    enemies.clear();
}

void World::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

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
}


void World::update()
{
    updateObjects();
    resolveCollisions();
    updateState();
    removeDeadObjects();
}

void World::updateObjects()
{
    player.update(*this);
    auto player_pos = player.getPosition();

    for (auto& enemy : enemies)
    {
        enemy->update(player_pos, *this);
    }

    for (auto& laser : player_lasers)
    {
	laser->update();
    }

    for (auto& laser : enemy_lasers)
    {
	laser->update();
    }
}

void World::resolveCollisions()
{
    resolvePlayerCollisions();
    resolveLaserCollisions();
}

void World::resolvePlayerCollisions()
{
    AABB player_hitbox = player.getHitbox();
    auto collides = [&player_hitbox] (const auto& enemy) {
	return enemy->collides(player_hitbox);
    };

    bool hit_by_laser = std::any_of(begin(enemy_lasers), end(enemy_lasers), collides);
    bool collides_with_enemy = std::any_of(begin(enemies), end(enemies), collides);

    if (collides_with_enemy || hit_by_laser)
    {
        player.kill();
    }
}

void World::resolveLaserCollisions()
{
    for (auto& laser : player_lasers)
    {
        for (auto& enemy : enemies)
	{
            if (laser->collides(enemy->getHitbox()))
	    {
                enemy->reduceHealth(laser->getDamage());
                laser->kill();
            }
        }
    }
}

void World::updateState()
{
    for (const auto& enemy : enemies)
    {
	if (enemy->isDead())
	{
	    state.score += enemy->getScore();
	}
    }

    state.player_dead = player.isDead();
    state.player_has_special = player.hasSpecialWeapon();
}

void World::removeDeadObjects()
{
    auto isDead = [] (const auto& object) { return object->isDead(); };

    enemies.erase(std::remove_if(begin(enemies), end(enemies), isDead), end(enemies));
    enemy_lasers.erase(std::remove_if(begin(enemy_lasers), end(enemy_lasers), isDead), end(enemy_lasers));
    player_lasers.erase(std::remove_if(begin(player_lasers), end(player_lasers), isDead), end(player_lasers));
}
