#include "missile.h"

Missile::Missile(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    // this->orientation = 0.0f;

    const int n = 24;

    GLfloat vertex_buffer_data[n * 9] = {};
    for(int i=0;i<n;i++){
        vertex_buffer_data[9 * i + 0] = radius_1 * cos(2 * M_PI/n * i);
        vertex_buffer_data[9 * i + 1] = -height/2;
        vertex_buffer_data[9 * i + 2] = radius_1 * sin(2 * M_PI/n * i);
        vertex_buffer_data[9 * i + 3] = radius_1 * cos(2 * M_PI/n * (i + 1));
        vertex_buffer_data[9 * i + 4] = -height/2;
        vertex_buffer_data[9 * i + 5] = radius_1 * sin(2 * M_PI/n * (i + 1 ));
        vertex_buffer_data[9 * i + 6] = radius_2 * (cos(2 * M_PI/n * i) + cos(2 * M_PI/n * (i + 1)))/2;
        vertex_buffer_data[9 * i + 7] = height/2;
        vertex_buffer_data[9 * i + 8] = radius_2 * (sin(2 * M_PI/n * i) + sin(2 * M_PI/n * (i + 1)))/2;
    }
    GLfloat vertex_buffer_data_2[n * 9] = {};
    for(int i=0;i<n;i++){
        vertex_buffer_data_2[9 * i + 0] = radius_2 * cos(2 * M_PI/n * i + M_PI/n);
        vertex_buffer_data_2[9 * i + 1] = height/2;
        vertex_buffer_data_2[9 * i + 2] = radius_2 * sin(2 * M_PI/n * i + M_PI/n);
        vertex_buffer_data_2[9 * i + 3] = radius_2 * cos(2 * M_PI/n * (i + 1) + M_PI/n);
        vertex_buffer_data_2[9 * i + 4] = height/2;
        vertex_buffer_data_2[9 * i + 5] = radius_2 * sin(2 * M_PI/n * (i + 1 ) + M_PI/n);
        vertex_buffer_data_2[9 * i + 6] = radius_1 * (cos(2 * M_PI/n * i + M_PI/n) + cos(2 * M_PI/n * (i + 1) + M_PI/n))/2;
        vertex_buffer_data_2[9 * i + 7] = -height/2;
        vertex_buffer_data_2[9 * i + 8] = radius_1 * (sin(2 * M_PI/n * i + M_PI/n) + sin(2 * M_PI/n * (i + 1) + M_PI/n))/2;
    }
    GLfloat vertex_buffer_data_3[n * 9] = {};
    for(int i=0;i<n;i++){
        vertex_buffer_data_3[9 * i + 0] = radius_2 * cos(2 * M_PI/n * i);
        vertex_buffer_data_3[9 * i + 1] = height/2;
        vertex_buffer_data_3[9 * i + 2] = radius_2 * sin(2 * M_PI/n * i);
        vertex_buffer_data_3[9 * i + 3] = radius_2 * cos(2 * M_PI/n * (i + 1));
        vertex_buffer_data_3[9 * i + 4] = height/2;
        vertex_buffer_data_3[9 * i + 5] = radius_2 * sin(2 * M_PI/n * (i + 1 ));
        vertex_buffer_data_3[9 * i + 6] = 0 * (cos(2 * M_PI/n * i) + cos(2 * M_PI/n * (i + 1)))/2;
        vertex_buffer_data_3[9 * i + 7] = nose_height + height/2;
        vertex_buffer_data_3[9 * i + 8] = 0 * (sin(2 * M_PI/n * i) + sin(2 * M_PI/n * (i + 1)))/2;
    }
    this->object[0] = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_PURPLE, GL_LINES);
    this->object[1] = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_2, COLOR_PINK, GL_LINES);
    this->object[2] = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data_3, COLOR_GREY, GL_LINES);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 orient    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 1));

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
}

void Missile::tick(){
    if(abs(this->position.x)>abs(ARENA) || abs(this->position.z)>abs(ARENA))
        this->position.y = GRAVE;
}

bounding_box_t Missile::get_bounding_box(){
    // bounding_box_t box = {
    //     this->position.x,   // x-coordinate of center
    //     this->position.y,   // y-coordinate of center
    //     this->position.z,   // z-coordinate of center
    //     radius_1*2,         // x dimension height
    //     height,             // y dimension height
    //     radius_1*2,             // z dimension height
    //     };
    // return box;
}
