#include "main.h"

// Include objects
#include "compass.h"
#include "frustum.h"
#include "island.h"
#include "missile.h"
#include "parachute.h"
#include "rafale.h"
#include "ring.h"
#include "sea.h"
#include "seven_segment.h"
#include "ship.h"
#include "tower.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
public:
    Engine() {}
    Engine(int level);
    void draw(glm::mat4 VP);
    void tick();
    void collider();
    void tick_input(GLFWwindow *window);
    glm::vec3 get_origin();
    glm::vec3 get_orientation();
private:
    Compass compass;
    Frustum frustum;
    Island island;
    Missile missile;
    Parachute parachute;
    Rafale rafale;
    Ring ring;
    Sea sea;
    Seven_segment altitude;
    Ship ship;
    Tower tower;
};

#endif // ENGINE_H
