#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x,float y,float z);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    void tick();
    bounding_box_t get_bounding_box();
private:
    VAO *object[3];
    float rotation;
    static constexpr float radius_1 = 0.06f;
    static constexpr float height = 0.3f;
    static constexpr float nose_height = 0.08f;
    static constexpr float radius_2 = 0.06f;
};

#endif // MISSILE_H
