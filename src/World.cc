#include "World.h"

#include <algorithm>
#include <numeric>

#include "AssetManager.h"
#include "Constants.h"
#include "Enums.h"
#include "Point.h"

World::World()
    : player {SDL_Rect {
		500,
		350,
		static_cast<int>(AssetManager::instance().getTexture("player")->getWidth() * 0.5),
		static_cast<int>(AssetManager::instance().getTexture("player")->getHeight() * 0.5)
	}} {}

WorldState World::getState() const
{
    return state;
}

void World::addEnemy(std::unique_ptr<Enemy> enemy)
{
    enemies.push_back(move(enemy));
}

void World::addEnemyLaser(const Point& origin, const Point& destination, float damage)
{
    auto texture = AssetManager::instance().getTexture("enemy_laser");
    float speed = 2.5;
    enemy_lasers.push_back({texture, origin, destination, damage, speed});
}

void World::addPlayerLaser(const Point& origin, float damage)
{
    auto texture = AssetManager::instance().getTexture("player_laser");
    float speed = 7.0;
    Point destination;
    SDL_GetMouseState(&destination.x, &destination.y);
    player_lasers.push_back({texture, origin, destination, damage, speed});
}

void World::addPowerup(const Powerup& powerup)
{
    powerups.push_back(powerup);
}

void World::killAllEnemies()
{
    for (auto& enemy : enemies)
    {
		enemy->kill();
    }

    for (auto& laser : enemy_lasers)
    {
		laser.kill();
    }
}

void World::draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::instance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);

    for (auto& enemy : enemies)
    {
		enemy->draw(renderer);
    }

    for (auto& laser : enemy_lasers)
    {
		laser.draw(renderer);
    }

    for (auto& laser : player_lasers)
    {
		laser.draw(renderer);
    }

    for (auto& powerup : powerups)
    {
		powerup.draw(renderer);
    }

    player.draw(renderer);
}


void World::update()
{
    updateObjects();
    resolveCollisions();
    resolvePowerups();
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
		laser.update();
    }

    for (auto& laser : enemy_lasers)
    {
		laser.update();
    }

    for (auto& powerup : powerups)
    {
		powerup.update();
    }
}

void World::resolveCollisions()
{
    resolvePlayerCollisions();
    resolveLaserCollisions();
}

void World::resolvePlayerCollisions()
{
    bool hit_by_laser = std::any_of(
		begin(enemy_lasers), end(enemy_lasers),
		[&] (const Laser& laser)
		{
			return laser.collides(player);
		});
    bool collides_with_enemy = std::any_of(
		begin(enemies), end(enemies),
		[&] (const auto& enemy)
		{
			return enemy->collides(player);
		});

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
            if (laser.collides(*enemy))
			{
                enemy->reduceHealth(laser.getDamage());
                laser.kill();
            }
        }
    }
}

void World::resolvePowerups()
{
    for (auto& powerup : powerups)
    {
		if (player.collides(powerup))
		{
			if (powerup.type() == PowerupType::BONUS_DAMAGE)
			{
				player.increaseDamage();
			}
			powerup.kill();
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
    auto isDead = [] (const auto& object) { return object.isDead(); };

    powerups.erase(std::remove_if(begin(powerups), end(powerups), isDead), end(powerups));

    enemy_lasers.erase(
		std::remove_if(begin(enemy_lasers), end(enemy_lasers), isDead),
		end(enemy_lasers)
		);

    player_lasers.erase(
		std::remove_if(begin(player_lasers), end(player_lasers), isDead),
		end(player_lasers)
		);

    enemies.erase(std::remove_if(begin(enemies), end(enemies),
								 [&] (const auto& enemy) {
									 return enemy->isDead();
								 }), end(enemies));
}
