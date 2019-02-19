#include "arrow.h"

Arrow::Arrow(float x, float z) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = (rand() % 180)/1.0f;
    this->speed = (rand() % 30)/ 200.0f - 0.15f;


    static const GLfloat vertex_buffer_data[] = {
       
    };
    static const GLfloat vertex_buffer_data_2[] = {
        length*0.9f,   height,    0.0f,
        0.0f,     height,    0.1f,
        0.0f,     height*2.5f,    0.0f,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_MAROON, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_2, COLOR_CREAM, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(0,1,0));

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[0]);
}

void Arrow::tick() {
    this->position.x -= cos(this->rotation * M_PI/180.0f) * this->speed;
    this->position.z += sin(this->rotation * M_PI/180.0f) * this->speed;
}
