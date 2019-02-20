#include "status_bar.h"

Status_bar::Status_bar(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);

    static const GLfloat vertex_buffer_data[] = {
       -thickness/2,    -height/2,   0.0f,
        thickness/2,    -height/2,   0.0f,
       -thickness/2,     height/2,   0.0f,
        thickness/2,     height/2,   0.0f,
       -thickness/2,     height/2,   0.0f,
        thickness/2,    -height/2,   0.0f,
    };
    static const GLfloat vertex_buffer_data_2[] = {
       -thickness*0.4f,    -height*0.45f,   0.0f,
        thickness*0.4f,    -height*0.45f,   0.0f,
       -thickness*0.4f,     height*0.45f,   0.0f,
        thickness*0.4f,     height*0.45f,   0.0f,
       -thickness*0.4f,     height*0.45f,   0.0f,
        thickness*0.4f,    -height*0.45f,   0.0f,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_2, COLOR_CREAM, GL_FILL);
}

void Status_bar::draw(float percent) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);

    // Rotate only needle
    Matrices.model = glm::mat4(1.0f);

    glm::mat4 scale = glm::scale(glm::vec3(1,percent,1));
    translate = glm::translate (this->position + glm::vec3(0,(1-percent) * height/2, 0));
    Matrices.model *= scale * translate;
    MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
}
