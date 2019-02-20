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

// Detect collision from object and plane
template <typename T> bool detect_collision_template(std::vector<T> &type, Rafale &rafale) {
    for (auto it = type.begin(); it != type.end(); it++) {
        if(detect_collision(it->get_bounding_box(), rafale.get_bounding_box())){
            rafale.die(1);
            it->die(1);
            return true;
        }
    }
}

// Detect collision from object and bomb
template <typename T> bool bomb_detect_collision_template(std::vector<T> &type, std::vector<Bomb> &bombs) {
    for (auto jt = bombs.begin(); jt != bombs.end(); jt++) {
        for (auto it = type.begin(); it != type.end(); it++) {
            if(detect_collision(it->get_bounding_box(), jt->get_bounding_box())){
                it->die(1);
                jt->die(1);
                return true;
            }
        }
    }
}

// Detect collision from object and bomb
template <typename T> bool missile_detect_collision_template(std::vector<T> &type, std::vector<Missile> &missiles) {
    for (auto jt = missiles.begin(); jt != missiles.end(); jt++) {
        for (auto it = type.begin(); it != type.end(); it++) {
            if(detect_collision(it->get_bounding_box(), jt->get_bounding_box())){
                it->die(1);
                jt->die(1);
                return true;
            }
        }
    }
}

Engine::Engine(int level) {
    this->counter = 0;
    this->score = 0;
    this->arrow = Arrow(0,3,3);

    //Dashboard Components
    this->altitude = Seven_segment(-0.25f,-0.85f,0);
    this->compass = Compass(0.85f,-0.85f,0);
    this->fuel_gauge = Odometer(-0.5f,-0.85f,0);
    this->odometer = Odometer(0.5f,-0.85f,0);
    this->health_bar = Status_bar(-0.85f, 0.0f, 0);

    this->rafale = Rafale(0,0);
    this->sea = Sea(SIDE * 1.5);
    this->target = Target(0,1,0);

    // this->cannon_balls.push_back()
    this->fuel_ups.push_back(Fuel_up(-6,6,-6));
    this->islands.push_back(Island(-8,-8));
    this->parachutes.push_back(Parachute(0,0));
    this->rings.push_back(Ring(2,1,-6));
    this->ships.push_back(Ship(0,4));
    this->towers.push_back(Tower(6,-10));
    this->volcanoes.push_back(Volcano(7,4));
}

void Engine::draw(glm::mat4 VP) {
    // Produce stuffs
    static const int GLOBAL = int(SIDE * 2);
    static const int LOCAL = GLOBAL;
    const int mod = int(LOCAL*2);
    const int norm = mod>>1;

    // Increment counter
    this->counter++;

    //Generate stuffs
    if(this->counter%11 == 7)
        this->parachutes.push_back(Parachute(rand()%mod - norm,rand()%mod - norm));
    if(this->counter%181 == 7)
        this->fuel_ups.push_back(Fuel_up(rand()%mod - norm,rand()%20,rand()%mod - norm));
    if(this->counter%179 == 7 && rings.size()<100)
        this->rings.push_back(Ring(rand()%mod-norm,rand()%20,rand()%mod-norm));
    if(this->counter%179 == 7 && ships.size()<100)
        this->ships.push_back(Ship(rand()%mod-norm,rand()%mod-norm));
    if(this->islands.size()<5)
        this->islands.push_back(Island(rand()%GLOBAL - SIDE, rand()%GLOBAL - SIDE));
    if(this->volcanoes.size()<40)
        this->volcanoes.push_back(Volcano(rand()%GLOBAL - SIDE, rand()%GLOBAL - SIDE));
    if(this->towers.size()<20)
        this->towers.push_back(Tower(rand()%GLOBAL - SIDE, rand()%GLOBAL - SIDE));

    if(this->counter%211 == 7)
        for (auto it = this->islands.begin(); it != this->islands.end(); it++) {
            this->cannon_balls.push_back(Cannon_ball(it->get_position(), this->rafale.get_position() - it->get_position()));
        }

    this->arrow.draw(VP,this->rafale.get_position() + 4.0f*this->rafale.unit_vector() + glm::vec3(0,1,0),glm::normalize(this->islands.begin()->get_position()-this->rafale.get_position()));
    this->target.draw(VP,this->rafale.get_position() +4.0f*this->rafale.unit_vector(),this->rafale.unit_vector());

    this->altitude.draw(this->score);
    this->compass.draw(this->rafale.unit_vector());
    this->fuel_gauge.draw(this->rafale.fuel_fill(0));
    this->odometer.draw(this->rafale.speed_fill());
    this->health_bar.draw(this->rafale.health_fill());

    draw_template(this->bombs, VP);
    draw_template(this->cannon_balls, VP);
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
    tick_template(this->bombs);
    tick_template(this->cannon_balls);
    tick_template(this->fuel_ups);
    tick_template(this->missiles);
    tick_template(this->parachutes);
    tick_template(this->ships);

    this->rafale.tick();
}

void Engine::collider() {

    // Detect collision with plane
    detect_collision_template(this->cannon_balls, this->rafale);
    detect_collision_template(this->islands, this->rafale);
    detect_collision_template(this->ships, this->rafale);
    detect_collision_template(this->towers, this->rafale);
    detect_collision_template(this->volcanoes, this->rafale);
    if(detect_collision_template(this->fuel_ups, this->rafale))
        this->rafale.fuel_fill(1);
    if(detect_collision_template(this->rings, this->rafale))
        this->score+=100;

    if(bomb_detect_collision_template(this->ships, this->bombs))
        this->score+=10;
    if(bomb_detect_collision_template(this->islands, this->bombs))
        this->score+=1000;

    // Detect collision with missile
    missile_detect_collision_template(this->volcanoes, this->missiles);
    missile_detect_collision_template(this->towers, this->missiles);
    if(missile_detect_collision_template(this->parachutes, this->missiles))
        this->score+=1;
    if(missile_detect_collision_template(this->ships, this->missiles))
        this->score+=10;
    if(missile_detect_collision_template(this->islands, this->missiles))
        this->score+=100;

}

void Engine::tick_input(GLFWwindow *window) {
    // Airplane controls
    int key_w = glfwGetKey(window, GLFW_KEY_W);
    int key_s = glfwGetKey(window, GLFW_KEY_S);
    int key_a = glfwGetKey(window, GLFW_KEY_A);
    int key_d = glfwGetKey(window, GLFW_KEY_D);
    int key_q = glfwGetKey(window, GLFW_KEY_Q);
    int key_e = glfwGetKey(window, GLFW_KEY_E);
    int key_z = glfwGetKey(window, GLFW_KEY_Z);
    int key_x = glfwGetKey(window, GLFW_KEY_X);
    int key_space = glfwGetKey(window, GLFW_KEY_SPACE);
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
    if(key_space) {
        //Clockwise roll control
        this->rafale.speed_up(true);
    }
    if(key_z) {
        //Clockwise roll control
        this->rafale.barral_roll();
    }
    if(key_x) {
        //Clockwise roll control
        this->rafale.loop();
    }
}

void Engine::mouse_handler(int button, int action) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            return;
        }
        else if (action == GLFW_RELEASE) {
            this->missiles.push_back(Missile(this->rafale.get_position(),this->rafale.unit_vector()));
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_RELEASE) {
            this->bombs.push_back(Bomb(this->rafale.get_position()));
        }
        break;
    default:
        break;
    }
}

glm::vec3 Engine::get_origin() {
    return this->rafale.get_position();
}

glm::vec3 Engine::get_orientation() {
    return rafale.orientation();
}

glm::vec3 Engine::unit_vector() {
    return this->rafale.unit_vector();
}
