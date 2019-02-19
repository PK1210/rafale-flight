#include "fuel_up.h"

Fuel_up::Fuel_up(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;


    static const GLfloat vertex_buffer_data[] = {
        side,   side,  0.0f,
       -side,   side,  0.0f,
       -side,  -side,  0.0f,
        side,   side,  0.0f,
       -side,  -side,  0.0f,
        side,  -side,  0.0f,
    };
    static const GLfloat vertex_buffer_data_2[] = {
         width, -0.75f * side,  0.0f,
        -width, -0.75f * side,  0.0f,
         width,  0.75f * side,  0.0f,
        -width,  0.75f * side,  0.0f,
         width,  0.75f * side,  0.0f,
        -width, -0.75f * side,  0.0f,
    };
    static const GLfloat vertex_buffer_data_3[] = {
        width * 0.75f, -0.25f * side + side/4,  0.0f,
       -width * 0.75f, -0.25f * side + side/4,  0.0f,
        width * 0.75f,  0.25f * side + side/4,  0.0f,
       -width * 0.75f,  0.25f * side + side/4,  0.0f,
        width * 0.75f,  0.25f * side + side/4,  0.0f,
       -width * 0.75f, -0.25f * side + side/4,  0.0f,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_RED, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3, COLOR_CREAM, GL_FILL);
}

void Fuel_up::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(0,1,0));

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
}

void Fuel_up::tick() {
    this->rotation++;
}

bounding_box_t Fuel_up::get_bounding_box(){
    bounding_box_t box = {
        this->position.x,   // x-coordinate of center
        this->position.y,   // y-coordinate of center
        this->position.z,   // z-coordinate of center
        side*2,         // x dimension height
        0.25f,             // y dimension height
        side*2,             // z dimension height
        };
    return box;
}

bool Fuel_up::die(bool force) {
    if(force)
        this->position.y = GRAVE;
    return this->position.y == GRAVE;
}
