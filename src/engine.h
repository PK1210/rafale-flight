#include "main.h"
#include <algorithm>

// Include objects
#include "bomb.h"
#include "compass.h"
#include "fuel_up.h"
#include "island.h"
#include "missile.h"
#include "parachute.h"
#include "rafale.h"
#include "ring.h"
#include "sea.h"
#include "seven_segment.h"
#include "ship.h"
#include "tower.h"
#include "volcano.h"

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
    int counter;
    Bomb bomb;
    Compass compass;
    Fuel_up fuel_up;
    Island island;
    Missile missile;
    std::vector<Parachute> parachutes;
    Rafale rafale;
    std::vector<Ring> rings;
    Sea sea;
    Seven_segment altitude;
    std::vector<Ship> ships;
    Tower tower;
    Volcano volcano;
};

#endif // ENGINE_H
