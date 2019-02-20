#include "main.h"

#ifndef Digit_display_H
#define Digit_display_H

const float SEGMENT_LENGTH = 0.025f;
const float THICKNESS = 0.003f;
const int MAX_DIGITS = 4;

const bool decoder[10][7] = {
    {1,1,1,1,1,1,0}, //0
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,1,1,0,1,1}, //5
    {1,0,1,1,1,1,1}, //6
    {1,1,1,0,0,0,0}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,1,0,1,1}  //9
};

const double vertex[7][3] = {
    {                0.0f, SEGMENT_LENGTH  , 0      },
    { SEGMENT_LENGTH/2.0f, SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    { SEGMENT_LENGTH/2.0f,-SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {                0.0f,-SEGMENT_LENGTH  , 0      },
    {-SEGMENT_LENGTH/2.0f,-SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {-SEGMENT_LENGTH/2.0f, SEGMENT_LENGTH/2.0f, M_PI/2.0f },
    {            0.0f ,             0.0f, 0      }
};
class Segment {
public:
    Segment() {}
    Segment(float x, float y, float z, float rotation, color_t color);
    glm::vec3 position;
    float rotation;
    void draw();
    void set_position(float x, float y, float z);
private:
    VAO *object;
};

class Digit_display {
public:
    Digit_display() {}
    Digit_display(float x, float y, float z, int digit);
    glm::vec3 position;
    float rotation;
    void draw();
    void set_position(float x, float y, float z);
private:
    Segment segments[7];
};

class Seven_segment {
public:
    Seven_segment() {}
    Seven_segment(float x, float y, float z);
    void draw(int number);
    void set_position(float x, float y, float z);
private:
    VAO *object;
    glm::vec3 position;
    Digit_display digits[MAX_DIGITS];
};

#endif // Digit_display_H
