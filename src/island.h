#include "main.h"

#ifndef ISLAND_H
#define ISLAND_H


class Island {
public:
    Island() {}
    Island(float x, float z);
    void draw(glm::mat4 VP);
    glm::vec3 position;
private:
    VAO *object[2];
    static constexpr float length = 4.0f;
    static constexpr float width  = 4.0f;
    static constexpr float height = 1.0f;
};

#endif // ISLAND_H
