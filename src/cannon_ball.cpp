#include "cannon_ball.h"

Cannon_ball::Cannon_ball(glm::vec3 position, glm::vec3 unit_vector) {
    this->position = position + glm::vec3(0,3.0f,0);
    this->rotation = 0;
    this->speed = (float)(rand()%MAX_SPEED)/(4 * MAX_SPEED) * unit_vector;
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

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_MILITARY, GL_FILL);
}

void Cannon_ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 1));
              rotate   *= glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
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
    this->rotation += 10.0f;
    if(abs(this->position.x)>abs(ARENA) || abs(this->position.z)>abs(ARENA))
        this->position.y = GRAVE;
    this->position += this->speed;
    this->speed.y -= GRAVITY * 2;
}

bounding_box_t Cannon_ball::get_bounding_box(){
    bounding_box_t box = {
        this->position.x,   // x-coordinate of center
        this->position.y,   // y-coordinate of center
        this->position.z,   // z-coordinate of center
        side,         // x dimension height
        side,             // y dimension height
        side,             // z dimension height
        };
    return box;
}

bool Cannon_ball::die(bool force) {
    if(force)
        this->position.y = GRAVE;
    return this->position.y == GRAVE;
}
