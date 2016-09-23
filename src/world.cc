#include "world.h"

#include <algorithm>
#include <numeric>

#include "point.h"
#include "constants.h"
#include "assets.h"
#include "enums.h"
#include "object_factory.h"

World::World()
    : player {SDL_Rect{ 500, 350,
	    static_cast<int>(Assets::getInstance().getTexture("player")->getWidth() * 0.5),
	    static_cast<int>(Assets::getInstance().getTexture("player")->getHeight() * 0.5) }} {}


void World::update()
{
    updateObjects();
    resolveCollisions();
    updateScore();
    removeDeadObjects();
    updateState();
}

WorldState World::getState() const
{
    return state;
}

void World::addEnemy(std::unique_ptr<Enemy> enemy)
{
    enemies.push_back(move(enemy));
}

void World::addPlayerLaser(const Point& origin, double damage)
{
    Point destination;
    SDL_GetMouseState(&destination.x, &destination.y);

    auto& factory = ObjectFactory::getInstance();
    player_lasers.push_back(factory.createPlayerLaser(origin, destination, damage));
}

void World::addEnemyLaser(const Point& origin, const Point& destination, double damage)
{
    auto& factory = ObjectFactory::getInstance();
    enemy_lasers.push_back(factory.createEnemyLaser(origin, destination, damage));
}


void World::killAllEnemies()
{
    for (auto& enemy : enemies)
    {
	enemy->kill();
    }
}

void World::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = Assets::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);

    auto draw = [&renderer] (auto& object) { object->draw(renderer); };
    std::for_each(begin(enemies), end(enemies), draw);
    std::for_each(begin(enemy_lasers), end(enemy_lasers), draw);
    std::for_each(begin(player_lasers), end(player_lasers), draw);
    player.draw(renderer);
}

void World::updateObjects()
{
    player.update(*this);

    auto player_pos = player.getPosition();
    for (auto& enemy : enemies)
    {
        enemy->update(player_pos, *this);
    }

    for (const auto& laser : player_lasers)
    {
	laser->update();
    }

    for (const auto& laser : enemy_lasers)
    {
	laser->update();
    }
}

void World::updateScore()
{
     state.score = std::accumulate(
	begin(enemies), end(enemies), state.score,
	[] (int sum, const auto& enemy)
	{ return enemy->isDead() ? sum + enemy->getScore() : sum; }
	);
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

void World::removeDeadObjects()
{
    auto isDead = [] (const auto& object) { return object->isDead(); };

    enemies.erase(std::remove_if(begin(enemies), end(enemies), isDead), end(enemies));
    player_lasers.erase(std::remove_if(begin(player_lasers), end(player_lasers),
				       isDead), end(player_lasers));
    enemy_lasers.erase(std::remove_if(begin(enemy_lasers), end(enemy_lasers), isDead),
		       end(enemy_lasers));
}


void World::updateState()
{
    state.player_dead = player.isDead();
    state.player_has_special = player.hasSpecialWeapon();
}
