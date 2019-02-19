#include "main.h"

#ifndef SHIP_H
#define SHIP_H


class Ship {
public:
    Ship() {}
    Ship(float x, float y);
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object[3];
    float rotation;
    float speed;
    glm::vec3 position;
    static constexpr float length= 2.0f;
    static constexpr float width = 1.0f;
    static constexpr float depth =-1.0f;
    static constexpr float height= 1.0f;
};

#endif // SHIP_H
