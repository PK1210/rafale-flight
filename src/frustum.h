#include "main.h"

#ifndef FRUSTUM_H
#define FRUSTUM_H


class Frustum {
public:
    Frustum() {}
    Frustum(float x, float y);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    void tick();
private:
    VAO *object[2];
    float rotation;
    static constexpr float radius_1 = 2.0f;
    static constexpr float height = 4.0f;
    static constexpr float radius_2 = 1.0f;
};

#endif // FRUSTUM_H
