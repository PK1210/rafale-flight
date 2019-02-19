#include "target.h"

Target::Target(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;

    static const GLfloat vertex_buffer_data[] = {
       -side/8,   thickness/2,  0.0f,
       -side/2,   thickness/2,  0.0f,
       -side/2,  -thickness/2,  0.0f,
       -side/8,   thickness/2,  0.0f,
       -side/2,  -thickness/2,  0.0f,
       -side/8,  -thickness/2,  0.0f,
    };
    static const GLfloat vertex_buffer_data_2[] = {
        side/2,   thickness/2,  0.0f,
        side/8,   thickness/2,  0.0f,
        side/8,  -thickness/2,  0.0f,
        side/2,   thickness/2,  0.0f,
        side/8,  -thickness/2,  0.0f,
        side/2,  -thickness/2,  0.0f,
    };
    static const GLfloat vertex_buffer_data_3[] = {
        thickness/2,   side/2,  0.0f,
       -thickness/2,   side/2,  0.0f,
       -thickness/2,   side/8,  0.0f,
        thickness/2,   side/2,  0.0f,
       -thickness/2,   side/8,  0.0f,
        thickness/2,   side/8,  0.0f,
    };
    static const GLfloat vertex_buffer_data_4[] = {
        thickness/2,  -side/8,  0.0f,
       -thickness/2,  -side/8,  0.0f,
       -thickness/2,  -side/2,  0.0f,
        thickness/2,  -side/8,  0.0f,
       -thickness/2,  -side/2,  0.0f,
        thickness/2,  -side/2,  0.0f,
    };
    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data  , COLOR_MILITARY, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_MILITARY, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3, COLOR_MILITARY, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_4, COLOR_MILITARY, GL_FILL);
}

void Target::draw(glm::mat4 VP, bool zoom) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(0,1,0));

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[0]);
}

void Target::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
