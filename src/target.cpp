#include "target.h"

Target::Target(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;

    static const GLfloat vertex_buffer_data[] = {
       -side/32,   thickness/2,  0.0f,
       -side/2,   thickness/2,  0.0f,
       -side/2,  -thickness/2,  0.0f,
       -side/32,   thickness/2,  0.0f,
       -side/2,  -thickness/2,  0.0f,
       -side/32,  -thickness/2,  0.0f,
    };
    static const GLfloat vertex_buffer_data_2[] = {
        side/2,   thickness/2,  0.0f,
        side/32,   thickness/2,  0.0f,
        side/32,  -thickness/2,  0.0f,
        side/2,   thickness/2,  0.0f,
        side/32,  -thickness/2,  0.0f,
        side/2,  -thickness/2,  0.0f,
    };
    static const GLfloat vertex_buffer_data_3[] = {
        thickness/2,   side/2,  0.0f,
       -thickness/2,   side/2,  0.0f,
       -thickness/2,   side/32,  0.0f,
        thickness/2,   side/2,  0.0f,
       -thickness/2,   side/32,  0.0f,
        thickness/2,   side/32,  0.0f,
    };
    static const GLfloat vertex_buffer_data_4[] = {
        thickness/2,  -side/32,  0.0f,
       -thickness/2,  -side/32,  0.0f,
       -thickness/2,  -side/2,  0.0f,
        thickness/2,  -side/32,  0.0f,
       -thickness/2,  -side/2,  0.0f,
        thickness/2,  -side/2,  0.0f,
    };
    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data  , COLOR_MILITARY, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_MILITARY, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3, COLOR_MILITARY, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_4, COLOR_MILITARY, GL_FILL);
}

void Target::draw(glm::mat4 VP, glm::vec3 new_position, glm::vec3 unit_vector) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (new_position);
    glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(0,1,0),unit_vector));
    float angle = glm::acos(glm::dot(glm::vec3(0,1,0),unit_vector)) - M_PI/2;
    glm::mat4 rotate = glm::rotate(angle, axis);

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
}
