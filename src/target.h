#include "main.h"

#ifndef TARGET_H
#define TARGET_H


class Target {
public:
    Target() {}
    Target(float x, float y, float z);
    void draw(glm::mat4 VP, glm::vec3 new_position, glm::vec3 unit_vector);
private:
    VAO *object[4];
    float rotation;
    glm::vec3 position;
    static constexpr float side  = 1.0f;
    static constexpr float thickness = 0.05f;
};

#endif // TARGET_H
