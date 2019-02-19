#include "main.h"

#ifndef TARGET_H
#define TARGET_H


class Target {
public:
    Target() {}
    Target(float x, float y, float z);
    void draw(glm::mat4 VP, bool zoom);
    glm::vec3 position;
private:
    VAO *object[6];
    static constexpr float width  = 4.0f;
    static constexpr float thickness = 0.4f;
};

#endif // TARGET_H
