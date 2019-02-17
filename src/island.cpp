#include "island.h"

Island::Island(float x, float z) {
    this->position = glm::vec3(x, height/2, z);

    static const GLfloat vertex_buffer_data[] = {
            -width/2, -height/2,  -width/2, // triangle 1 : begin
            -width/2, -height/2,   width/2,
            -width/2,  height/2,   width/2, // triangle 1 : end
             width/2,  height/2,  -width/2, // triangle 2 : begin
            -width/2, -height/2,  -width/2,
            -width/2,  height/2,  -width/2, // triangle 2 : end

             width/2,  height/2,  -width/2,
             width/2, -height/2,  -width/2,
            -width/2, -height/2,  -width/2,
            -width/2, -height/2,  -width/2,
            -width/2,  height/2,   width/2,
            -width/2,  height/2,  -width/2,

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
            -width/2,  height/2,   width/2,
             width/2, -height/2,   width/2
        };

    static const GLfloat vertex_buffer_data_2[] = {
            width/2, -height/2,   width/2,
           -width/2, -height/2,  -width/2,
            width/2, -height/2,  -width/2,
            width/2, -height/2,   width/2,
           -width/2, -height/2,   width/2,
           -width/2, -height/2,  -width/2,
            width/2,  height/2,   width/2,
            width/2,  height/2,  -width/2,
           -width/2,  height/2,  -width/2,
            width/2,  height/2,   width/2,
           -width/2,  height/2,  -width/2,
           -width/2,  height/2,   width/2
        };

    this->object[0] = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, COLOR_OCHRE, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_2, COLOR_GRASS, GL_FILL);
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    // glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(1,0,0));

    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}
