#include "ring.h"

Ring::Ring(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = -90.0f;

    const int n = 24;

    GLfloat vertex_buffer_data[n * 9] = {};
    for(int i=0;i<n;i++){
        vertex_buffer_data[9 * i + 0] = radius_1 * cos(2 * M_PI/n * i);
        vertex_buffer_data[9 * i + 1] = -height/2;
        vertex_buffer_data[9 * i + 2] = radius_1 * sin(2 * M_PI/n * i);
        vertex_buffer_data[9 * i + 3] = radius_1 * cos(2 * M_PI/n * (i + 1));
        vertex_buffer_data[9 * i + 4] = -height/2;
        vertex_buffer_data[9 * i + 5] = radius_1 * sin(2 * M_PI/n * (i + 1 ));
        vertex_buffer_data[9 * i + 6] = radius_2 * (cos(2 * M_PI/n * i) + cos(2 * M_PI/n * (i + 1)))/2;
        vertex_buffer_data[9 * i + 7] = height/2;
        vertex_buffer_data[9 * i + 8] = radius_2 * (sin(2 * M_PI/n * i) + sin(2 * M_PI/n * (i + 1)))/2;
    }
    GLfloat vertex_buffer_data_2[n * 9] = {};
    for(int i=0;i<n;i++){
        vertex_buffer_data_2[9 * i + 0] = radius_2 * cos(2 * M_PI/n * i);
        vertex_buffer_data_2[9 * i + 1] = height/2;
        vertex_buffer_data_2[9 * i + 2] = radius_2 * sin(2 * M_PI/n * i);
        vertex_buffer_data_2[9 * i + 3] = radius_2 * cos(2 * M_PI/n * (i + 1));
        vertex_buffer_data_2[9 * i + 4] = height/2;
        vertex_buffer_data_2[9 * i + 5] = radius_2 * sin(2 * M_PI/n * (i + 1 ));
        vertex_buffer_data_2[9 * i + 6] = radius_1 * (cos(2 * M_PI/n * i) + cos(2 * M_PI/n * (i + 1)))/2;
        vertex_buffer_data_2[9 * i + 7] = -height/2;
        vertex_buffer_data_2[9 * i + 8] = radius_1 * (sin(2 * M_PI/n * i) + sin(2 * M_PI/n * (i + 1)))/2;
    }
    this->object[0] = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_PINK, GL_LINES);
    this->object[1] = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_2, COLOR_CREAM, GL_LINES);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}
