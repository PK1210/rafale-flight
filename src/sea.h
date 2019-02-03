#include "main.h"

#ifndef SEA_H
#define SEA_H

class Sea {
public:
    Sea() {}
    Sea(float side);
    void draw(glm::mat4 VP);
private:
    VAO* object;
    glm::vec3 position;
};

#endif // SEA_H
