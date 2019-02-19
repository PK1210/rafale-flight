#include "compass.h"

Compass::Compass(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;


    static const GLfloat vertex_buffer_data[] = {
        side,   side,  0.0f,
       -side,   side,  0.0f,
       -side,  -side,  0.0f,
        side,   side,  0.0f,
       -side,  -side,  0.0f,
        side,  -side,  0.0f,
    };
    static const GLfloat vertex_buffer_data_2[] = {
         width,  0.0f,   0.0f,
        -width,  0.0f,   0.0f,
          0.0f,  0.9*side,   0.0f,
    };
    static const GLfloat vertex_buffer_data_3[] = {
         width,  0.0f,   0.0f,
        -width,  0.0f,   0.0f,
          0.0f, -0.9*side,   0.0f,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_2, COLOR_RED, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_3, COLOR_CREAM, GL_FILL);
}

void Compass::draw(glm::mat4 VP, glm::vec3 unit_vector, glm::vec3 dashboard_normal) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);

    // Rotate only needle
    Matrices.model = glm::mat4(1.0f);
    float angle = glm::acos(glm::dot(unit_vector, glm::vec3(0,0,1)));

    // Find sign through cross product
    if(glm::cross(unit_vector,glm::vec3(0,0,1)).y < 0)
        angle*=-1;
    glm::mat4 rotate = glm::rotate(angle, dashboard_normal);
    Matrices.model *= translate * rotate;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
}
