#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float z);
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object[3];
    float speed;
    glm::vec3 position;
    // For parachute
    static constexpr float radius = 0.5f;
    static constexpr float height = 0.25f;

    static constexpr float space = 0.5f;

    static constexpr float length = 0.25f;
    static constexpr float width  = 0.25f;
    static constexpr float depth = 0.25f;
};

#endif // PARACHUTE_H
