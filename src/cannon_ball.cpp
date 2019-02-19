#include "cannon_ball.h"

Cannon_ball::Cannon_ball(float x, float y, float z, float speed) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = speed;
    float width = side;
    float height = side;
    float depth = side;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
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

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
}

void Cannon_ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon_ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon_ball::tick() {
    this->rotation += 10;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
