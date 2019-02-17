#include "ship.h"

Ship::Ship(float x, float z) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = (rand() % 180)/1.0f;
    this->speed = (rand() % 30)/ 100.0f - 0.15f;


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
        0.0f,     height,    0.0f,
        0.0f,     height*2.5f,    0.0f,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data_2, COLOR_RED, GL_FILL);
}

void Ship::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(1,0,0));

    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[0]);
}

void Ship::tick() {
    this->position.x += sin(this->rotation * M_PI/180.0f) * this->speed;
    this->position.z += cos(this->rotation * M_PI/180.0f) * this->speed;
}
