#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <string>

#include "moving_object.h"

class Player: public MovingObject {
public:
    Player(Texture*, int, int, int, int);
    bool hasSingularity() const; // Checks if the player has singularity
    void move() override;
    void update(const std::map<std::string, bool>&, function<void()>&); 
    void update() override;
    void setSingularity(bool);
    std::pair<int, int> getPosistion() const;

private:
    bool carries_singularity;
    Uint32 shoot_cooldown;
    void setAngle();
    void shoot();
};

#endif
