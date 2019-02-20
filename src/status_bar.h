#include "main.h"

#ifndef STATUS_H
#define STATUS_H


class Status_bar {
public:
    Status_bar() {}
    Status_bar(float x, float y, float z);
    void draw(float percent);
    void set_position(glm::vec3 position);
private:
    VAO *object[2];
    glm::vec3 position;
    static constexpr float height = 1.0f;
    static constexpr float thickness = 0.125f;
};

#endif // STATUS_H
