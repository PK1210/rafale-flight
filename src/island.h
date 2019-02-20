#include "main.h"
#include "cannon.h"

#ifndef ISLAND_H
#define ISLAND_H


class Island {
public:
    Island() {}
    Island(float x, float z);
    void draw(glm::mat4 VP);
    glm::vec4 * shoot();
    bounding_box_t get_bounding_box();
    bool die(bool);
    glm::vec3 get_position();
private:
    VAO *object[6];
    Cannon cannon;
    glm::vec3 position;
    float max_height;
    static constexpr float width  = 4.0f;
    static constexpr float height = 0.4f;
};

#endif // ISLAND_H
