#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x,float y,float z);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    void tick();
    bounding_box_t get_bounding_box();
private:
    VAO *object[5];
    float rotation;
    float speed;
    static constexpr float radius_1 = 0.25f;
    static constexpr float height = 1.0f;
    static constexpr float radius_2 = 0.5f;
};

#endif // BOMB_H
