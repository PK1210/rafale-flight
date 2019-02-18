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

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(0,1,0));

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
}

void Compass::tick() {
    // this->position.x -= cos(this->rotation * M_PI/180.0f) * this->speed;
    // this->position.z += sin(this->rotation * M_PI/180.0f) * this->speed;
}
