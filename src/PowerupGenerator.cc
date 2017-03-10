#include "PowerupGenerator.h"

#include "AssetManager.h"
#include "Constants.h"
#include "DoubleDamage.h"

void PowerupGenerator::update(World& world)
{
    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_spawn_time > spawn_delay_ms)
    {
	spawnPowerup(world);
    }
}

void PowerupGenerator::spawnPowerup(World& world)
{
    Point pos = getSpawnPoint();
    SDL_Rect hitbox {
	pos.x,
	pos.y,
	50,
	50
    };

    std::uniform_int_distribution<int> range(0, powerups.size());
    std::string powerup = powerups[range(random)];

    if (powerup == "doubledamage")
    {
	auto texture = AssetManager::getInstance().getTexture("doubledamage");
	world.addPowerup(std::make_unique<GameObject>(texture, hitbox, 0));
    }
}

Point PowerupGenerator::getSpawnPoint()
{
    int x_min = constants::SCREEN_WIDTH / 4;
    int x_max = constants::SCREEN_WIDTH * ( 3/4 );
    int y_min = constants::SCREEN_HEIGHT / 4;
    int y_max = constants::SCREEN_HEIGHT * ( 3/4 );

    std::uniform_int_distribution<int> range_x(x_min, x_max);
    std::uniform_int_distribution<int> range_y(y_min, y_max);

    Point point;
    point.x = range_x(random);
    point.y = range_y(random);

    return point;
}
