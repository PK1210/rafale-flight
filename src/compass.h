#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z);
    void draw(glm::mat4 VP, glm::vec3 unit_vector, glm::vec3 dashboard_normal);
    void set_position(glm::vec3 position);
private:
    VAO *object[3];
    float rotation;
    glm::vec3 position;
    static constexpr float side = 0.5f;
    static constexpr float width = 0.1f;
};

#endif // COMPASS_H
