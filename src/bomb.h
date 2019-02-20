#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(glm::vec3 new_position);
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object[5];
    glm::vec3 position;
    float rotation;
    float speed;
    static constexpr float radius_1 = 0.125f;
    static constexpr float height = 0.5f;
    static constexpr float radius_2 = 0.25f;
};

#endif // BOMB_H
