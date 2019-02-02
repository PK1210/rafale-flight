#include "rafale.h"
#include "main.h"

Rafale::Rafale(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    this->yaw_ctrl = 0;
    this->pitch_ctrl = 0;
    this->roll_ctrl = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            -width, -height,  -depth, // triangle 1 : begin
            -width, -height,   depth,
            -width,  height,   depth, // triangle 1 : end
             width,  height,  -depth, // triangle 2 : begin
            -width, -height,  -depth,
            -width,  height,  -depth, // triangle 2 : end
             width, -height,   depth,
            -width, -height,  -depth,
             width, -height,  -depth,
             width,  height,  -depth,
             width, -height,  -depth,
            -width, -height,  -depth,
            -width, -height,  -depth,
            -width,  height,   depth,
            -width,  height,  -depth,
             width, -height,   depth,
            -width, -height,   depth,
            -width, -height,  -depth,
            -width,  height,   depth,
            -width, -height,   depth,
             width, -height,   depth,
             width,  height,   depth,
             width, -height,  -depth,
             width,  height,  -depth,
             width, -height,  -depth,
             width,  height,   depth,
             width, -height,   depth,
             width,  height,   depth,
             width,  height,  -depth,
            -width,  height,  -depth,
             width,  height,   depth,
            -width,  height,  -depth,
            -width,  height,   depth,
             width,  height,   depth,
            -width,  height,   depth,
             width, -height,   depth
        };
        static const GLfloat vertex_buffer_data_2[] = {
            //fin 1
            -width,   0.0f,  -depth/8, // triangle 1 : begin
            -width,   0.0f, 7*depth/8,
       -span-width,   0.0f,   depth/2, // triangle 1 : end
            -width,   0.0f,-7*depth/8, // triangle 2 : begin
            -width,   0.0f,  -depth/4,
     -span/2-width,   0.0f,  -depth/2, // triangle 2 : end
            // fin 2
             width,   0.0f, 7*depth/8, // triangle 1 : begin
             width,   0.0f,  -depth/8,
        span+width,   0.0f,   depth/2, // triangle 1 : end
             width,   0.0f,-7*depth/8, // triangle 2 : begin
             width,   0.0f,  -depth/4,
      span/2+width,   0.0f,  -depth/2, // triangle 2 : end
            // fin 3
              0.0f,span/2+height,   depth, // triangle 1 : begin
              0.0f,       height,   depth/2,
              0.0f,       height,   depth, // triangle 1 : end
            // Nose
              0.0f,      0.0f,   -depth-span/2,
             width,    height,   -depth,
            -width,    height,   -depth,
              0.0f,      0.0f,   -depth-span/2,
            -width,    height,   -depth,
            -width,   -height,   -depth,
              0.0f,      0.0f,   -depth-span/2,
            -width,   -height,   -depth,
             width,   -height,   -depth,
              0.0f,      0.0f,   -depth-span/2,
             width,   -height,   -depth,
             width,    height,   -depth
        };
        static const GLfloat vertex_buffer_data_3[] = {
            width/2, span/4+height,  -depth/4,
            width/2,        height,  -depth/4,
               0.0f,        height,-7*depth/8,
           -width/2, span/4+height,  -depth/4,
           -width/2,        height,  -depth/4,
               0.0f,        height,-7*depth/8,
            width/2, span/4+height,  -depth/4,
           -width/2, span/4+height,  -depth/4,
               0.0f,        height,-7*depth/8,
           -width/2, span/4+height,  -depth/4,
           -width/2,        height,  -depth/4,
            width/2, span/4+height,  -depth/4,
            width/2,        height,  -depth/4,
            width/2, span/4+height,  -depth/4,
           -width/2,        height,  -depth/4
        };

    this->object[0] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data , COLOR_RED, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES,  9*3, vertex_buffer_data_2, COLOR_GREEN, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES,  5*3, vertex_buffer_data_3, COLOR_BLUE, GL_FILL);
}

void Rafale::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate *= glm::rotate((float) (this->yaw_ctrl * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate *= glm::rotate((float) (this->pitch_ctrl * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate *= glm::rotate((float) (this->roll_ctrl * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
}

void Rafale::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rafale::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Rafale::pitch(bool up) {
    if(up)
        this->pitch_ctrl += 1;
    else
        this->pitch_ctrl -= 1;
}

void Rafale::yaw(bool right) {
    if(right)
        this->yaw_ctrl += 1;
    else
        this->yaw_ctrl -= 1;
}

void Rafale::roll(bool anticlockwise) {
    if(anticlockwise)
        this->roll_ctrl += 1;
    else
        this->roll_ctrl -= 1;
}
