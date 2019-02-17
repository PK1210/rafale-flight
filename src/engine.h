#include "main.h"

// Include objects
#include "frustum.h"
#include "island.h"
#include "parachute.h"
#include "rafale.h"
#include "sea.h"
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
private:
    Frustum frustum;
    Island island;
    Parachute parachute;
    Rafale rafale;
    Ship ship;
    Sea sea;
    Tower tower;
};

#endif // ENGINE_H
