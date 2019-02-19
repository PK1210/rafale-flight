#include "ship.h"

Ship::Ship(float x, float z) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = (rand() % 180)/1.0f;
    this->speed = (rand() % 30)/ 200.0f - 0.15f;


    static const GLfloat vertex_buffer_data[] = {
        length,    height,   width,
       -length,    height,   width,
        0.0f,     depth,    0.0f,
       -length,    height,   width,
       -length,    height,  -width,
        0.0f,     depth,    0.0f,
       -length,    height,  -width,
        length,    height,  -width,
        0.0f,     depth,    0.0f,
        length,    height,  -width,
        length,    height,   width,
        0.0f,     depth,    0.0f,
    };
    static const GLfloat vertex_buffer_data_2[] = {
        length*0.9f,   height,    0.0f,
        0.0f,     height,    0.1f,
        0.0f,     height*2.5f,    0.0f
    };
    static const GLfloat vertex_buffer_data_3[] = {
         length, height, -width,
        -length, height, -width,
         length, height,  width,
        -length, height,  width,
         length, height,  width,
        -length, height, -width,
    };
    this->object[0] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_MAROON, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_2, COLOR_CREAM, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3, COLOR_OCHRE, GL_FILL);
}

void Ship::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(0,1,0));

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[0]);
}

void Ship::tick() {
    this->position.x -= cos(this->rotation * M_PI/180.0f) * this->speed;
    this->position.z += sin(this->rotation * M_PI/180.0f) * this->speed;
    if(abs(this->position.x)>abs(ARENA) || abs(this->position.z)>abs(ARENA))
        this->position.y = GRAVE;
}

bounding_box_t Ship::get_bounding_box(){
    bounding_box_t box = {
        this->position.x,   // x-coordinate of center
        this->position.y,   // y-coordinate of center
        this->position.z,   // z-coordinate of center
        length*2,         // x dimension height
        height*4,         // y dimension height
        width,             // z dimension height
        };
        return box;
}
