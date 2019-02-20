#include "main.h"

#ifndef BOX_H
#define BOX_H


class Cannon_ball {
public:
    Cannon_ball() {}
    Cannon_ball(float x, float y, float z, float speed);
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object;
    float speed;
    glm::vec3 position;
    float rotation;
    static constexpr float side = 0.5f;
};

#endif // BOX_H
