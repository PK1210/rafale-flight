#include "main.h"
#include <algorithm>

// Include objects
#include "arrow.h"
#include "bomb.h"
#include "cannon_ball.h"
#include "compass.h"
#include "fuel_up.h"
#include "island.h"
#include "missile.h"
#include "odometer.h"
#include "parachute.h"
#include "rafale.h"
#include "ring.h"
#include "sea.h"
#include "seven_segment.h"
#include "ship.h"
#include "target.h"
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
    void mouse_handler(int button,int action);
    glm::vec3 get_origin();
    glm::vec3 get_orientation();
    glm::vec3 unit_vector();
private:
    int counter;
    int score;
    Arrow arrow;
    Compass compass;
    Odometer fuel_gauge;
    Odometer odometer;
    Rafale rafale;
    Sea sea;
    Seven_segment altitude;
    Target target;

    std::vector<Bomb> bombs;
    std::vector<Cannon_ball> cannon_balls;
    std::vector<Fuel_up> fuel_ups;
    std::vector<Island> islands;
    std::vector<Missile> missiles;
    std::vector<Parachute> parachutes;
    std::vector<Ring> rings;
    std::vector<Ship> ships;
    std::vector<Tower> towers;
    std::vector<Volcano> volcanoes;
};

#endif // ENGINE_H
