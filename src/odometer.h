#include "main.h"

#ifndef ODOMETER_H
#define ODOMETER_H


class Odometer {
public:
    Odometer() {}
    Odometer(float x, float y, float z);
    void draw(glm::mat4 VP, float percent, glm::vec3 dashboard_normal);
    void set_position(glm::vec3 position);
private:
    VAO *object[2];
    glm::vec3 position;
    float rotation;
    static constexpr float radius = 0.5f;
    static constexpr float thickness = 0.05f;
};

#endif // ODOMETER_H
