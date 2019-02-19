#include "island.h"

//function to make island
void set_vertex_buffer(float width,float height,float height_addent,int index,VAO * object[])
{
     GLfloat vertex_buffer_data[] = {
            -width/2, -height/2+height_addent,  -width/2, // triangle 1 : begin
            -width/2, -height/2+height_addent,   width/2,
            -width/2,  height/2+height_addent,   width/2, // triangle 1 : end
             width/2,  height/2+height_addent,  -width/2, // triangle 2 : begin
            -width/2, -height/2+height_addent,  -width/2,
            -width/2,  height/2+height_addent,  -width/2, // triangle 2 : end

             width/2,  height/2+height_addent,  -width/2,
             width/2, -height/2+height_addent,  -width/2,
            -width/2, -height/2+height_addent,  -width/2,
            -width/2, -height/2+height_addent,  -width/2,
            -width/2,  height/2+height_addent,   width/2,
            -width/2,  height/2+height_addent,  -width/2,

            -width/2,  height/2+height_addent,   width/2,
            -width/2, -height/2+height_addent,   width/2,
             width/2, -height/2+height_addent,   width/2,
             width/2,  height/2+height_addent,   width/2,
             width/2, -height/2+height_addent,  -width/2,
             width/2,  height/2+height_addent,  -width/2,
             width/2, -height/2+height_addent,  -width/2,
             width/2,  height/2+height_addent,   width/2,
             width/2, -height/2+height_addent,   width/2,


             width/2,  height/2+height_addent,   width/2,
            -width/2,  height/2+height_addent,   width/2,
             width/2, -height/2+height_addent,   width/2
        };

     GLfloat vertex_buffer_data_2[] = {
            width/2, -height/2+height_addent,   width/2,
           -width/2, -height/2+height_addent,  -width/2,
            width/2, -height/2+height_addent,  -width/2,
            width/2, -height/2+height_addent,   width/2,
           -width/2, -height/2+height_addent,   width/2,
           -width/2, -height/2+height_addent,  -width/2,
            width/2,  height/2+height_addent,   width/2,
            width/2,  height/2+height_addent,  -width/2,
           -width/2,  height/2+height_addent,  -width/2,
            width/2,  height/2+height_addent,   width/2,
           -width/2,  height/2+height_addent,  -width/2,
           -width/2,  height/2+height_addent,   width/2
        };
        object[index+0] = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, COLOR_OCHRE, GL_FILL);
        object[index+1] = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data_2, COLOR_GRASS, GL_FILL);
}

Island::Island(float x, float z) {
    this->position = glm::vec3(x, height/2, z);

    set_vertex_buffer(width,height,0,0,this->object);
    set_vertex_buffer(width-1,height,height,2,this->object);
    set_vertex_buffer(width-2,height,height*2,4,this->object);

    this->cannon = Cannon(x, height*3, z);
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    // glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI/180.0f), glm::vec3(1,0,0));

    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<6;i++)
        draw3DObject(this->object[i]);
    this->cannon.draw(VP);
}

glm::vec4 * Island::shoot() {
    return this->cannon.shoot();
}

bounding_box_t Island::get_bounding_box(){
    bounding_box_t box = {
        this->position.x,   // x-coordinate of center
        this->position.y,   // y-coordinate of center
        this->position.z,   // z-coordinate of center
        width,         // x dimension height
        height*5,         // y dimension height
        width,             // z dimension height
        };
    return box;
}

bool Island::die(bool force) {
    if(force)
        this->position.y = GRAVE;
    return this->position.y == GRAVE;
}
