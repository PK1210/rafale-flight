#include "engine.h"

Engine::Engine(int level) {
    this->sea = Sea(100);
    this->rafale = Rafale(0,0);
}

void Engine::draw(glm::mat4 VP) {
    this->sea.draw(VP);
    this->rafale.draw(VP);
}

void Engine::tick() {
    this->rafale.tick();
}

void Engine::tick_input(GLFWwindow *window) {
    // Airplane controls
    int key_w = glfwGetKey(window, GLFW_KEY_W);
    int key_s = glfwGetKey(window, GLFW_KEY_S);
    int key_a = glfwGetKey(window, GLFW_KEY_A);
    int key_d = glfwGetKey(window, GLFW_KEY_D);
    int key_q = glfwGetKey(window, GLFW_KEY_Q);
    int key_e = glfwGetKey(window, GLFW_KEY_E);
    if(key_w) {
        //Pitch up control
        this->rafale.pitch(true);
    }
    if(key_s) {
        //Pitch down control
        this->rafale.pitch(false);
    }
    if(key_a) {
        //Left control
        this->rafale.yaw(false);
    }
    if(key_d) {
        //Right control
        this->rafale.yaw(true);
    }
    if(key_q) {
        //Counterclockwise roll control
        this->rafale.roll(true);
    }
    if(key_e) {
        //Clockwise roll control
        this->rafale.roll(false);
    }

    // int key_ = glfwGetKey(window, GLFW_KEY_);
    // int key_ = glfwGetKey(window, GLFW_KEY_);
    // if(key_) {
    //     // control
    //     rafale.();
    // }
    // if(key_) {
    //     // control
    //     rafale.();
    // }
}

glm::vec3 Engine::get_origin() {
    return rafale.position;
}
