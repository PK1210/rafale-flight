#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(glm::vec3 position);
    void draw(glm::mat4 VP, glm::vec3 unit_vector, glm::vec3 dashboard_normal);
    void set_position(glm::vec3 position);
private:
    VAO *object[2];
    glm::vec3 position;
    float rotation;
    static constexpr float side = 0.5f;
    static constexpr float thickness = 0.1f;
};

#endif // DASHBOARD_H
