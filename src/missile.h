#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(glm::vec3 position, glm::vec3 unit_vector);
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object[3];
    float rotation;
    glm::vec3 position;
    glm::vec3 orientation;
    static constexpr float radius_1 = 0.12f;
    static constexpr float height = 0.6f;
    static constexpr float nose_height = 0.16f;
    static constexpr float radius_2 = 0.12f;
    static constexpr float speed = 1.25f;
};

#endif // MISSILE_H
