#include "tower.h"

Tower::Tower(float x, float y) {
    this->position = glm::vec3(x, height/2, y);

    static const GLfloat vertex_buffer_data[] = {
            -width/2, -height/2,  -depth/2, // triangle 1 : begin
            -width/2, -height/2,   depth/2,
            -width/2,  height/2,   depth/2, // triangle 1 : end
             width/2,  height/2,  -depth/2, // triangle 2 : begin
            -width/2, -height/2,  -depth/2,
            -width/2,  height/2,  -depth/2, // triangle 2 : end
             width/2, -height/2,   depth/2,
            -width/2, -height/2,  -depth/2,
             width/2, -height/2,  -depth/2,
             width/2,  height/2,  -depth/2,
             width/2, -height/2,  -depth/2,
            -width/2, -height/2,  -depth/2,
            -width/2, -height/2,  -depth/2,
            -width/2,  height/2,   depth/2,
            -width/2,  height/2,  -depth/2,
             width/2, -height/2,   depth/2,
            -width/2, -height/2,   depth/2,
            -width/2, -height/2,  -depth/2,
            -width/2,  height/2,   depth/2,
            -width/2, -height/2,   depth/2,
             width/2, -height/2,   depth/2,
             width/2,  height/2,   depth/2,
             width/2, -height/2,  -depth/2,
             width/2,  height/2,  -depth/2,
             width/2, -height/2,  -depth/2,
             width/2,  height/2,   depth/2,
             width/2, -height/2,   depth/2,
             width/2,  height/2,   depth/2,
             width/2,  height/2,  -depth/2,
            -width/2,  height/2,  -depth/2,
             width/2,  height/2,   depth/2,
            -width/2,  height/2,  -depth/2,
            -width/2,  height/2,   depth/2,
             width/2,  height/2,   depth/2,
            -width/2,  height/2,   depth/2,
             width/2, -height/2,   depth/2
        };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data , COLOR_BLACK, GL_FILL);
}

void Tower::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

glm::vec3 Tower::get_position() {
    return this->position;
}
