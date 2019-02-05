#include "main.h"

// Include objects
#include "sea.h"
#include "tower.h"
#include "rafale.h"

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
    Rafale rafale;
    Sea sea;
    Tower tower;
};

#endif // ENGINE_H
