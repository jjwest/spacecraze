#include "../inc/blaster.h"
#include "../inc/globals.h"

Blaster::Blaster(Texture* t, int x, int y, 
                 int s, int hp, double a, std::vector<Laser*>* v, 
                 Texture* l,
                 std::pair<double, double>* p_pos)
    : Moving_Object(t, x, y, s, hp, a), shots_fired{v}, 
    lasertexture{l}, aim_at{p_pos}, last_shot{0}, score{40} {}


void Blaster::shoot() // Creates a laserobject and pushes it to vector, all blasters share a vector
{
    Uint32 current_time = SDL_GetTicks();

    if( current_time - last_shot > 300 )
    {
        std:: pair<int, int> aim_to;
        aim_to.first = static_cast<int> (aim_at->first);
        aim_to.second = static_cast<int> (aim_at->second);
        set_angle();
    
        shots_fired->push_back(new Laser(lasertexture, rect.x + (rect.h/2), rect.y + (rect.w/2), speed*2, 
                                         1000, angle-180, 1, aim_to));

        last_shot = current_time;
    }
}

void Blaster::change_direction() 
{
    std::random_device randint;
    std::uniform_int_distribution<int> random_x(0, 1024);
    std::uniform_int_distribution<int> random_y(0, 768);

    if( rect.y - rect.h <= 0 )
    {
        go_to.first = random_x(randint);
        go_to.second = SCREEN_HEIGHT;
    }
    else if( rect.y + rect.h >= SCREEN_HEIGHT )
    {
        go_to.first = random_x(randint);
        go_to.second = 0;
    }
    else if( rect.x - rect.w <= 0 )
    {
        go_to.second = random_y(randint);
        go_to.first = SCREEN_WIDTH;
    }
    else if( rect.x + rect.w >= SCREEN_WIDTH )
    {
        go_to.second = random_y(randint);
        go_to.first = 0;
    }
}

void Blaster::move() 
{
    change_direction();
    double center_blaster_x = rect.x + (rect.h / 2);  
    double center_blaster_y = rect.y + (rect.w / 2);
    
    double x_dist = go_to.first - center_blaster_x;
    double y_dist = go_to.second - center_blaster_y;
    double longest = std::max(abs(x_dist), abs(y_dist));
    
    double delta_x = x_dist / longest;
    double delta_y = y_dist /longest;
    
    double move_x = delta_x * speed;
    double move_y = delta_y * speed;

    rect.x = rect.x + static_cast<int>(round(move_x));
    rect.y = rect.y + static_cast<int>(round(move_y));

    set_angle();
}

void Blaster::update()
{
    move();
    shoot();
    update_AABB();
}

void Blaster::set_angle()
{
    // Calculates angle to player
     int center_x, center_y;
     float ang;
          
     center_x = rect.x + (rect.h / 2);
     center_y = rect.y + (rect.w / 2);
     
     ang = atan2(center_y - aim_at->second, center_x - aim_at->first);
     ang = ang * 180 / M_PI;
     
     angle = (static_cast<int> (ang) + 90)%360;
}

int Blaster::get_score() const
{
    return score;
}

