#include "main.h"

#ifndef BOX_H
#define BOX_H


class Box {
public:
    Box() {}
    Box(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BOX_H
