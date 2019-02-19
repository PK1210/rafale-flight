#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    void tick();
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object[2];
    float rotation;
    static constexpr float radius_1 = 1.25f;
    static constexpr float height = 0.25f;
    static constexpr float radius_2 = 1.0f;
};

#endif // RING_H
