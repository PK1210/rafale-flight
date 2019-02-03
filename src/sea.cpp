#include "sea.h"

Sea::Sea(float side) {
    this->position = glm::vec3(0, 0, 0);

    static const GLfloat vertex_buffer_data[] = {
         side, 0.0f,  side,
        -side, 0.0f,  side,
        -side, 0.0f, -side,
         side, 0.0f,  side,
         side, 0.0f, -side,
        -side, 0.0f, -side
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data , COLOR_SEA_BLUE, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
