#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    glm::vec4 * shoot();
private:
    VAO *object[2];
    float rotation;
    int shoot_timer;
    static constexpr int wait_time = 1;
    static constexpr float radius_1 = 0.8f;
    static constexpr float height   = 1.5f;
    static constexpr float radius_2 = 0.6f;
};

#endif // CANNON_H
