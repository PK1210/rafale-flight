#include "engine.h"

// Filter
template <typename T> bool filter(T& type) { return type.die(0); }

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

// Detect collision from object
template <typename T> bool detect_collision_template(std::vector<T> &type, Rafale &rafale) {
    for (auto it = type.begin(); it != type.end(); it++) {
        // bounding_box_t temp1 = rafale.get_bounding_box();
        // bounding_box_t temp2 = it->get_bounding_box();
        // printf("%f %f %f %f %f %f\n",temp1.x,temp1.y,temp1.z,temp2.x,temp2.y,temp2.z);
        if(detect_collision(it->get_bounding_box(), rafale.get_bounding_box())){
            // rafale.die();
            it->die(1);
            printf("Hi collision\n");
            return true;
        }
    }
}

Engine::Engine(int level) {
    this->counter = 0;
    this->altitude = Seven_segment(1,2,1,0);
    this->compass = Compass(4,4,0);
    this->rafale = Rafale(0,0);
    this->sea = Sea(SIDE);
    this->target = Target(0,1,0);

    this->fuel_ups.push_back(Fuel_up(-6,6,-6));
    this->islands.push_back(Island(-8,-8));
    this->missiles.push_back(Missile(0,3,1));
    this->parachutes.push_back(Parachute(0,0));
    this->rings.push_back(Ring(2,1,-6));
    this->ships.push_back(Ship(0,4));
    this->towers.push_back(Tower(6,-10));
    this->volcanoes.push_back(Volcano(7,4));
}

void Engine::draw(glm::mat4 VP) {
    this->altitude.draw(VP);
    this->compass.draw(VP);
    this->target.draw(VP,false);

    draw_template(this->bombs, VP);
    draw_template(this->fuel_ups, VP);
    draw_template(this->islands, VP);
    draw_template(this->missiles, VP);
    draw_template(this->parachutes, VP);
    draw_template(this->rings, VP);
    draw_template(this->ships, VP);
    draw_template(this->towers, VP);
    draw_template(this->volcanoes, VP);

    this->rafale.draw(VP);
    this->sea.draw(VP);

}

void Engine::tick() {

    // Produce stuffs
    static const int LOCAL = 50;
    const int mod = int(LOCAL*2);
    const int norm = mod>>1;

    // Increment counter
    this->counter++;

    //Generate stuffs
    if(this->counter%79 == 7)
        this->parachutes.push_back(Parachute(rand()%mod - norm,rand()%mod - norm));
    if(this->counter%179 == 7 && rings.size()<100)
        this->rings.push_back(Ring(rand()%mod-norm,rand()%mod,rand()%mod-norm));
    if(this->counter%379 == 7 && ships.size()<100)
        this->ships.push_back(Ship(rand()%mod-norm,rand()%mod-norm));

    this->compass.tick();

    tick_template(this->bombs);
    tick_template(this->fuel_ups);
    tick_template(this->missiles);
    tick_template(this->parachutes);
    tick_template(this->ships);

    this->rafale.tick();

    //Check shoots and shoot
    // glm::vec4 * check = this->island.shoot();
    // if(check){
    //     printf("%f %f %f\n",check->x,check->y,check->z);
    // }
}

void Engine::collider() {
    detect_collision_template(this->fuel_ups, this->rafale);
    detect_collision_template(this->islands, this->rafale);
    detect_collision_template(this->rings, this->rafale);
    detect_collision_template(this->ships, this->rafale);
    detect_collision_template(this->towers, this->rafale);
    detect_collision_template(this->volcanoes, this->rafale);
    // detect_collision_template(this->volcanoes, this->rafale);
    // detect_collision_template(this->volcanoes, this->rafale);
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

void Engine::mouse_handler(int button, int action) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            printf("Breathless\n");
            return;
        }
        else if (action == GLFW_RELEASE) {
            printf("Breath\n");
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_RELEASE) {
            this->bombs.push_back(Bomb(this->rafale.position.x, this->rafale.position.y, this->rafale.position.z));
        }
        break;
    default:
        break;
    }
}

glm::vec3 Engine::get_origin() {
    return rafale.position;
}

glm::vec3 Engine::get_orientation() {
    return rafale.orientation();
}
