#include "main.h"

#ifndef TARGET_H
#define TARGET_H


class Target {
public:
    Target() {}
    Target(float x, float y, float z);
    void draw(glm::mat4 VP, bool zoom);
    void set_position(float x, float y, float z);
private:
    VAO *object[4];
    float rotation;
    glm::vec3 position;
    static constexpr float side  = 1.0f;
    static constexpr float thickness = 0.1f;
};

#endif // TARGET_H
