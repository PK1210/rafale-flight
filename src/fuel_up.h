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
private:
    VAO *object[3];
    float rotation;
    static constexpr float side = 0.4f;
    static constexpr float width = 0.2f;
};

#endif // FUEL_UP_H
