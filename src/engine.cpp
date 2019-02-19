#include "engine.h"

// Filter
template <typename T> bool filter(T& type) { return (type.position.y < GRAVE); }

// Render object
template <typename T> void draw_template(std::vector<T> &type, glm::mat4 VP) {
    type.erase(std::remove_if(type.begin(), type.end(), filter<T>), type.end());
    for (auto it = type.begin(); it != type.end(); it++)
        it->draw(VP);
}

//Tick object
template <typename T> void tick_template(std::vector<T> &type) {
    for (auto it = type.begin(); it != type.end(); it++)
        it->tick();
}

Engine::Engine(int level) {
    this->counter = 0;
    this->altitude = Seven_segment(1,2,1,4);
    this->bomb = Bomb(2,2,-2);
    this->compass = Compass(4,4,0);
    this->fuel_up = Fuel_up(2,4,-2);
    this->island = Island(-2,-2);
    this->missile = Missile(0,3,1);
    this->parachutes.push_back(Parachute(0,0));
    this->rings.push_back(Ring(2,1,-6));
    this->rafale = Rafale(0,0);
    this->ships.push_back(Ship(0,-4));
    this->sea = Sea(SIDE);
    this->tower = Tower(6,-10);
    this->volcano = Volcano(4,5);
}

void Engine::draw(glm::mat4 VP) {
    this->altitude.draw(VP);
    this->bomb.draw(VP);
    this->compass.draw(VP);
    this->fuel_up.draw(VP);
    this->volcano.draw(VP);
    this->island.draw(VP);
    this->missile.draw(VP);
    draw_template(this->parachutes, VP);
    draw_template(this->rings, VP);
    draw_template(this->ships, VP);
    this->rafale.draw(VP);
    this->sea.draw(VP);
    this->tower.draw(VP);
}

void Engine::tick() {

    // Produce stuffs
    static const int LOCAL = 50;
    const int mod = int(LOCAL*2);
    const int norm = mod>>1;

    // Increment counter
    this->counter++;

    if(this->counter%215 == 7)
        this->parachutes.push_back(Parachute(rand()%mod - norm,rand()%mod - norm));
    if(this->counter%379 == 7 && rings.size()<100)
        this->rings.push_back(Ring(rand()%mod-norm,rand()%mod,rand()%mod-norm));
    if(this->counter%379 == 7 && rings.size()<100)
        this->ships.push_back(Ship(rand()%mod-norm,rand()%mod-norm));

    this->bomb.tick();
    this->compass.tick();
    this->fuel_up.tick();
    this->missile.tick();
    tick_template(this->parachutes);
    tick_template(this->ships);
    this->rafale.tick();

    //Check shoots and shoot
    glm::vec4 * check = this->island.shoot();
    if(check){
        printf("%f %f %f\n",check->x,check->y,check->z);
    }
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
}

glm::vec3 Engine::get_origin() {
    return rafale.position;
}

glm::vec3 Engine::get_orientation() {
    return rafale.orientation();
}
