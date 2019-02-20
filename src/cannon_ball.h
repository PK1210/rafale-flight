#include "main.h"

#ifndef BOX_H
#define BOX_H


class Cannon_ball {
public:
    Cannon_ball() {}
    Cannon_ball(glm::vec3 position, glm::vec3 unit_vector);
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object;
    glm::vec3 speed;
    glm::vec3 position;
    float rotation;
    static constexpr float side = 0.5f;
    static constexpr int MAX_SPEED = 20;
};

#endif // BOX_H
