#include<unistd.h>

#include "main.h"
#include "engine.h"
#include "timer.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Engine engine;

const float width = 1482.5;
const float height = 1020;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

// Eye - Location of camera.
glm::vec3 eye (0, 2, 10);

// Target - Where is the camera looking at.
glm::vec3 target(0, 0, 0);

glm::vec3 up(0, 1, 0);
// Up - Up vector defines tilt of camera.

Timer t60(1.0 / 60);

int View_controller = 1;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    glUseProgram (programID);

    // Compute Camera matrix (view)
    target = engine.get_origin();

    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    Matrices.projection = glm::perspective(glm::radians(45.0f), float(width)/float(height), 0.1f, 150.f);
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    engine.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int follow_cam_view = glfwGetKey(window, GLFW_KEY_1);
    int top_view = glfwGetKey(window, GLFW_KEY_2);
    int plane_view = glfwGetKey(window, GLFW_KEY_3);
    int tower_view = glfwGetKey(window, GLFW_KEY_4);
    int helicopter_view = glfwGetKey(window, GLFW_KEY_5);
    if(follow_cam_view)
        View_controller = 1;
    if(top_view)
        View_controller = 2;
    if(plane_view)
        View_controller = 3;
    if(tower_view)
        View_controller = 4;
    if(helicopter_view)
        View_controller = 5;

    engine.tick_input(window);
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    engine.mouse_handler(button,action);
}

void tick_elements() {
    // Check for collision
    engine.collider();

    engine.tick();
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */

    engine = Engine(1);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            switch(View_controller)
            {
                case 1:{
                    target = engine.get_origin();
                    float theta = engine.get_orientation().x;
                    theta = glm::radians(theta);
                    eye = glm::vec3 (target.x + 8*sin(theta), target.y + 4, target.z + 8*cos(theta));
                    up = glm::vec3 (0,1,0);
                    break;
                }
                case 2:{
                    target = engine.get_origin();
                    eye = glm::vec3 (target.x, target.y + 32, target.z);
                    up = glm::vec3 (0,0,-1);
                    break;
                }
                case 3:{
                    glm::vec3 position = engine.get_origin();
                    glm::vec3 theta = engine.get_orientation();
                    eye = glm::vec3 (position.x, position.y, position.z);
                    target = engine.get_origin();
                    up = glm::vec3 (0,0,-1);
                    break;
                }
                case 4:{
                    eye = glm::vec3 (6,25,-10);
                    target = engine.get_origin();
                    up = glm::vec3 (0,100,0);
                    break;
                }
                case 5:{
                    eye = glm::vec3 (6,8,-10);
                    target = engine.get_origin();
                    up = glm::vec3 (0,100,0);
                    break;
                }
            }
            // dashboard.set_position(eye+glm::normalize(target-eye)*)
            // dashboard.set_rotation(eye-target, up)
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();

        // Add usleep
        usleep(10000);
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
