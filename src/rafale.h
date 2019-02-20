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
    void speed_up(bool up);
    float speed_fill();
    glm::vec3 get_position();
    void die(int sick);
    float health_fill();
    void barral_roll();
    void loop();
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
    float health;
    int barral_roll_ctrl;
    int loop_ctrl;
    static constexpr float width = 0.3f;
    static constexpr float height = 0.3f;
    static constexpr float depth = 0.9f;
    static constexpr float span = 0.8f;
    static constexpr int MAX_FUEL = 1000;
    static constexpr int MAX_HEALTH = 20;
    static constexpr float MAX_SPEED = 1.0f;
};

#endif // RAFALE_H
