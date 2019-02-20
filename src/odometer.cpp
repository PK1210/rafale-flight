#include "odometer.h"

Odometer::Odometer(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;


    const int n = 8;

    static GLfloat vertex_buffer_data[n * 9];
    for(int i=0;i<n;i++){
        vertex_buffer_data[9 * i + 0] = 0.0f;
        vertex_buffer_data[9 * i + 1] = 0.0f;
        vertex_buffer_data[9 * i + 2] = 0.0f;
        vertex_buffer_data[9 * i + 3] = radius * cos(2.0f * M_PI/n * i);
        vertex_buffer_data[9 * i + 4] = radius * sin(2.0f * M_PI/n * i);
        vertex_buffer_data[9 * i + 5] = 0.0f;
        vertex_buffer_data[9 * i + 6] = radius * cos(2.0f * M_PI/n * (i + 1));
        vertex_buffer_data[9 * i + 7] = radius * sin(2.0f * M_PI/n * (i + 1));
        vertex_buffer_data[9 * i + 8] = 0.0f;
    }

    static const GLfloat vertex_buffer_data_2[] = {
        -0.8*radius,  0.0f,   0.0f,
           0.0f, thickness,   0.0f,
           0.0f,-thickness,   0.0f,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, n*3+6, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_2, COLOR_YELLOW, GL_FILL);
}

void Odometer::draw(float percent) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);

    // Rotate only needle
    Matrices.model = glm::mat4(1.0f);
    float angle = -glm::asin(percent)-M_PI/2;

    glm::mat4 rotate = glm::rotate(angle, glm::vec3(0,0,1));
    Matrices.model *= translate * rotate;
    MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
}

void Odometer::set_position(glm::vec3 new_position) {
    this->position = new_position;
}
