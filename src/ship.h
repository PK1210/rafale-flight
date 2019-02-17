#include "main.h"

#ifndef SHIP_H
#define SHIP_H


class Ship {
public:
    Ship() {}
    Ship(float x, float y);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    void tick();
private:
    VAO *object[2];
    float rotation;
    float speed;
    static constexpr float length= 2.0f;
    static constexpr float width = 1.0f;
    static constexpr float depth =-1.0f;
    static constexpr float height= 1.0f;
};

#endif // SHIP_H
