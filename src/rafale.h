#include "main.h"

#ifndef RAFALE_H
#define RAFALE_H


class Rafale {
public:
    Rafale() {}
    Rafale(float x, float y);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void yaw(bool right);
    void pitch(bool up);
    void roll(bool anticlockwise);
    glm::vec3 position;
    glm::vec3 orientation();
    bounding_box_t get_bounding_box();
    bool shoot();
    glm::vec3 unit_vector();
    float fuel_fill(bool up);
    glm::vec3 get_position();
private:
    VAO *object[4];
    glm::mat4 rotation_matrix;
    float rotation;
    float speed;
    float counter;
    float yaw_ctrl;
    float pitch_ctrl;
    float roll_ctrl;
    int fuel;
    static constexpr float width = 0.3f;
    static constexpr float height = 0.3f;
    static constexpr float depth = 0.9f;
    static constexpr float span = 0.8f;
    static constexpr int MAX_FUEL = 10000;
    static constexpr float MAX_SPEED = 1.0f;
};

#endif // RAFALE_H
