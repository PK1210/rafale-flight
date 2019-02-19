#include "main.h"

#ifndef FUEL_UP_H
#define FUEL_UP_H


class Fuel_up {
public:
    Fuel_up() {}
    Fuel_up(float x, float y, float z);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    void tick();
    bounding_box_t get_bounding_box();
private:
    VAO *object[3];
    float rotation;
    static constexpr float side = 0.4f;
    static constexpr float width = side/2;
};

#endif // FUEL_UP_H
