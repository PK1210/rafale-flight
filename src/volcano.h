#include "main.h"

#ifndef FRUSTUM_H
#define FRUSTUM_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float z);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object[3];
    float rotation;
    static constexpr float radius_1 = 4.0f;
    static constexpr float height = 8.0f;
    static constexpr float radius_2 = 2.0f;
};

#endif // FRUSTUM_H
