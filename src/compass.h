#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z);
    void draw(glm::vec3 unit_vector);
    void set_position(glm::vec3 position);
private:
    VAO *object[3];
    float rotation;
    glm::vec3 position;
    static constexpr float side = 0.05f;
    static constexpr float width = 0.01f;
};

#endif // COMPASS_H
