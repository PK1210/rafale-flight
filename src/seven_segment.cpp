#include "seven_segment.h"
#include "main.h"

Segment::Segment(float x, float y,float z,float rotation, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rotation;

   static const GLfloat vertex_buffer_data[] = {
       SEGMENT_LENGTH/2.0f, THICKNESS/2.0f, 0.0f, // triangle 1 : begin
      -SEGMENT_LENGTH/2.0f, THICKNESS/2.0f, 0.0f,
      -SEGMENT_LENGTH/2.0f,-THICKNESS/2.0f, 0.0f, // triangle 1 : end
       SEGMENT_LENGTH/2.0f,-THICKNESS/2.0f, 0.0f, // triangle 2 : begin
      -SEGMENT_LENGTH/2.0f,-THICKNESS/2.0f, 0.0f,
       SEGMENT_LENGTH/2.0f, THICKNESS/2.0f, 0.0f, // triangle 2 : end
   };
   this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Segment::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -width, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Segment::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

Digit_display::Digit_display(float x, float y, float z, int digit) {
    this->position = glm::vec3(x, y, z);
    for(int i=0; i<7; i++){
        if(!decoder[digit][i])
            this->segments[i] = Segment(x + vertex[i][0], y + vertex[i][1], z, vertex[i][2], COLOR_LIGHT_GREEN);
        else
            this->segments[i] = Segment(x + vertex[i][0], y + vertex[i][1], z, vertex[i][2], COLOR_DARK_GREEN);
    }
}

void Digit_display::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    for(int i=0;i<7;i++) {
        this->segments[i].draw(VP);
    }
}

void Digit_display::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

Seven_segment::Seven_segment(float x, float y, float z, int num) {
    this->position = glm::vec3(x, y, z);
    this->count = MAX_DIGITS;

    for(int i=0;i<MAX_DIGITS;i++){
        this->digits[i] = Digit_display(x + (MAX_DIGITS-i-1) * SEGMENT_LENGTH * 1.25f + SEGMENT_LENGTH, y, z, num%10);
        num = num/10;
    }

    float width = SEGMENT_LENGTH * MAX_DIGITS * 1.5f;
    float height = SEGMENT_LENGTH * 2.5;

    static const GLfloat vertex_buffer_data[] = {
              width, height/2.0f, 0.0f, // triangle 1 : begin
               0.0f, height/2.0f, 0.0f,
              width,-height/2.0f, 0.0f, // triangle 1 : end
               0.0f, height/2.0f, 0.0f, // triangle 2 : begin
               0.0f,-height/2.0f, 0.0f,
              width,-height/2.0f, 0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Seven_segment::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of  around which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    for(int i=0;i<this->count;i++) {
        this->digits[i].draw(VP);
    }
};

void Seven_segment::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
