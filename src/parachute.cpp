#include "parachute.h"

Parachute::Parachute(float x, float z) {
    this->position = glm::vec3(x, 12.5f, z);
    this->speed = 0;

    const int n = 6;

    static GLfloat vertex_buffer_data[n * 9];
    for(int i=0;i<n;i++){
        vertex_buffer_data[9 * i + 0] = 0.0f;
        vertex_buffer_data[9 * i + 1] = height;
        vertex_buffer_data[9 * i + 2] = 0.0f;
        vertex_buffer_data[9 * i + 3] = radius * cos(2 * M_PI/n * i);
        vertex_buffer_data[9 * i + 4] = 0.0f;
        vertex_buffer_data[9 * i + 5] = radius * sin(2 * M_PI/n * i);
        vertex_buffer_data[9 * i + 6] = radius * cos(2 * M_PI/n * (i + 1));
        vertex_buffer_data[9 * i + 7] = 0.0f;
        vertex_buffer_data[9 * i + 8] = radius * sin(2 * M_PI/n * (i + 1));
    }
    static const GLfloat vertex_buffer_data_2[] = {
        radius/2, height/4, radius/2,
       -radius/2, height/4,-radius/2,
          0.0f,   -space,   0.0f,
        radius/2, height/4,-radius/2,
       -radius/2, height/4, radius/2,
          0.0f,   -space,   0.0f,
    };

    static const GLfloat vertex_buffer_data_3[] = {
            -length/2, -width/2-space,  -depth/2, // triangle 1 : begin
            -length/2, -width/2-space,   depth/2,
            -length/2,  width/2-space,   depth/2, // triangle 1 : end
             length/2,  width/2-space,  -depth/2, // triangle 2 : begin
            -length/2, -width/2-space,  -depth/2,
            -length/2,  width/2-space,  -depth/2, // triangle 2 : end
             length/2, -width/2-space,   depth/2,
            -length/2, -width/2-space,  -depth/2,
             length/2, -width/2-space,  -depth/2,
             length/2,  width/2-space,  -depth/2,
             length/2, -width/2-space,  -depth/2,
            -length/2, -width/2-space,  -depth/2,
            -length/2, -width/2-space,  -depth/2,
            -length/2,  width/2-space,   depth/2,
            -length/2,  width/2-space,  -depth/2,
             length/2, -width/2-space,   depth/2,
            -length/2, -width/2-space,   depth/2,
            -length/2, -width/2-space,  -depth/2,
            -length/2,  width/2-space,   depth/2,
            -length/2, -width/2-space,   depth/2,
             length/2, -width/2-space,   depth/2,
             length/2,  width/2-space,   depth/2,
             length/2, -width/2-space,  -depth/2,
             length/2,  width/2-space,  -depth/2,
             length/2, -width/2-space,  -depth/2,
             length/2,  width/2-space,   depth/2,
             length/2, -width/2-space,   depth/2,
             length/2,  width/2-space,   depth/2,
             length/2,  width/2-space,  -depth/2,
            -length/2,  width/2-space,  -depth/2,
             length/2,  width/2-space,   depth/2,
            -length/2,  width/2-space,  -depth/2,
            -length/2,  width/2-space,   depth/2,
             length/2,  width/2-space,   depth/2,
            -length/2,  width/2-space,   depth/2,
             length/2, -width/2-space,   depth/2
        };

    this->object[0] = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_ORANGE, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_GREY, GL_LINE);
    this->object[2] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_3, COLOR_MAROON, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    // glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(1,0,0));

    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[2]);
}

void Parachute::tick() {
    this->speed += GRAVITY/10;
    this->position.y -= this->speed;
}

bounding_box_t Parachute::get_bounding_box(){
    bounding_box_t box = {
        this->position.x,   // x-coordinate of center
        this->position.y-width/2-space,   // y-coordinate of center
        this->position.z,   // z-coordinate of center
        length,         // x dimension height
        width+space,         // y dimension height
        depth,             // z dimension height
        };
    return box;
}
