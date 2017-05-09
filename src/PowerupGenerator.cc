#include "PowerupGenerator.h"

#include "AssetManager.h"
#include "Constants.h"

#include <iostream>

PowerupGenerator::PowerupGenerator()
{
    powerups.push_back("doubledamage");
}

void PowerupGenerator::update(World& world)
{
    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_spawn_time > spawn_delay_ms)
    {
	spawnPowerup(world);
	last_spawn_time = current_time;
    }
}

void PowerupGenerator::spawnPowerup(World& world)
{
    Point pos = getSpawnPoint();
    SDL_Rect hitbox {
	pos.x,
	pos.y,
	30,
	30
    };

    std::uniform_int_distribution<int> range(0, powerups.size() - 1);
    std::string powerup = powerups[ range(random) ];

    if (powerup == "doubledamage")
    {
	auto texture = AssetManager::getInstance().getTexture("doubledamage");
	world.addPowerup(Powerup(texture, hitbox, PowerupType::BONUS_DAMAGE));
    }
}

Point PowerupGenerator::getSpawnPoint()
{
    int x_min = SCREEN_WIDTH / 10;
    int x_max = SCREEN_WIDTH * 0.90;
    int y_min = SCREEN_HEIGHT / 10;
    int y_max = SCREEN_HEIGHT * 0.90;

    std::uniform_int_distribution<int> range_x(x_min, x_max);
    std::uniform_int_distribution<int> range_y(y_min, y_max);

    Point point;
    point.x = range_x(random);
    point.y = range_y(random);

    return point;
}
