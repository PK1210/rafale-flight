#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    void tick();
private:
    VAO *object[2];
    float rotation;
    float speed;
    static constexpr float length= 2.0f;
    static constexpr float width = 1.0f;
    static constexpr float height= 1.0f;
};

#endif // ARROW_H
