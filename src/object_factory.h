#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include <memory>

#include "asteroid.h"
#include "blaster.h"
#include "drone.h"
#include "laser.h"

class ObjectFactory
{
public:
    ObjectFactory(const ObjectFactory&) = delete;
    ObjectFactory& operator=(const ObjectFactory&) = delete;
    static ObjectFactory& getInstance();
    std::unique_ptr<Enemy> createEnemy(const std::string& type);
    std::unique_ptr<Laser> createLaser(const std::string& type,
                                       const Point& pos,
                                       const Point& destination,
                                       double dmg);
    
private:
    ObjectFactory() {};
};


#endif // _OBJECT_FACTORY_H_
