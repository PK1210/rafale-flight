#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    void draw(glm::mat4 VP, glm::vec3 new_position, glm::vec3 unit_vector);
private:
    VAO *object[2];
    glm::vec3 position;
    static constexpr float width = 0.05f;
    static constexpr float height= 0.3f;
};

#endif // ARROW_H
