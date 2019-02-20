#include "arrow.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);

    static const GLfloat vertex_buffer_data[] = {
            -width/2, -height/2,  -width/2, // triangle 1 : begin
            -width/2, -height/2,   width/2,
            -width/2,  height/2,   width/2, // triangle 1 : end
             width/2,  height/2,  -width/2, // triangle 2 : begin
            -width/2, -height/2,  -width/2,
            -width/2,  height/2,  -width/2, // triangle 2 : end
             width/2, -height/2,   width/2,
            -width/2, -height/2,  -width/2,
             width/2, -height/2,  -width/2,
             width/2,  height/2,  -width/2,
             width/2, -height/2,  -width/2,
            -width/2, -height/2,  -width/2,
            -width/2, -height/2,  -width/2,
            -width/2,  height/2,   width/2,
            -width/2,  height/2,  -width/2,
             width/2, -height/2,   width/2,
            -width/2, -height/2,   width/2,
            -width/2, -height/2,  -width/2,
            -width/2,  height/2,   width/2,
            -width/2, -height/2,   width/2,
             width/2, -height/2,   width/2,
             width/2,  height/2,   width/2,
             width/2, -height/2,  -width/2,
             width/2,  height/2,  -width/2,
             width/2, -height/2,  -width/2,
             width/2,  height/2,   width/2,
             width/2, -height/2,   width/2,
             width/2,  height/2,   width/2,
             width/2,  height/2,  -width/2,
            -width/2,  height/2,  -width/2,
             width/2,  height/2,   width/2,
            -width/2,  height/2,  -width/2,
            -width/2,  height/2,   width/2,
             width/2,  height/2,   width/2,
            -width/2,  height/2,   width/2,
             width/2, -height/2,   width/2
        };
        static const GLfloat vertex_buffer_data_2[] = {
             width, 0.5f * height, width,
              0.0f,0.75f * height,  0.0f,
            -width, 0.5f * height, width,
            -width, 0.5f * height, width,
              0.0f,0.75f * height,  0.0f,
            -width, 0.5f * height,-width,
            -width, 0.5f * height,-width,
              0.0f,0.75f * height,  0.0f,
             width, 0.5f * height,-width,
             width, 0.5f * height,-width,
              0.0f,0.75f * height,  0.0f,
             width, 0.5f * height, width,
        };

    this->object[0] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_2, COLOR_RED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP, glm::vec3 new_position, glm::vec3 unit_vector) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (new_position);
    glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(0,1,0),unit_vector));
    float angle = glm::acos(glm::dot(glm::vec3(0,1,0),unit_vector));
    glm::mat4 rotate = glm::rotate(angle, axis);

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[0]);
}
