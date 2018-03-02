#include <iostream>

#include <GL.hpp>
#include <GLFW.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <logger.hpp>
#include <types.hpp>
#include <readers.hpp>

#include "Subsystems/Rendering/Resources/shaders.hpp"
#include "Subsystems/Rendering/Resources/geometry.hpp"
#include "Subsystems/Rendering/Resources/texture.hpp"
#include "Subsystems/Rendering/camera.hpp"

using namespace Rendering::Resources;

//TODO: create proxy input class
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos) noexcept;

void process_input(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static float last_timestamp = 0.0f;
static glm::dvec2 last_mouse_pos;

bool first = true;//FIXME: a bit dirty hack for mouse input delta

glm::vec4 ambient = {0.1f, 0.1f, 0.1f, 1.0f}; //rgb + intensity

struct Light_source
{
    glm::vec3 color = {1.0f, 1.0f, 1.0f}; //White by default
    glm::vec3 scale = {0.1f, 0.1f, 0.1f};
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::vec4 rotation = {0.0f, 1.0f, 0.0f, 0.0f};//{xyz, degrees} //TODO: make this glm::quat

    Geometry::pointer geometry = nullptr;
    Shader_program::pointer program = nullptr;
};

struct Object
{
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::vec3 scale = {1.0f, 1.0f, 1.0f};
    glm::vec4 rotation = {0.0f, 1.0f, 0.0f, 0.0f};//{xyz, degrees} //TODO: make this glm::quat

    Geometry::pointer geometry = nullptr;
    Shader_program::pointer program = nullptr;

    Texture::pointer diffuse = nullptr;
    Texture::pointer specular = nullptr;
};

Camera camera(glm::dvec3(0.0, 0.0, -3.0), glm::dvec3(0.0, 0.0, 0.0),
              glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f));

template<typename T>
void export_common_data(T &object)
{
    glm::mat4 model;
    model = glm::rotate(model, glm::radians(object.rotation.w),
                        glm::vec3(object.rotation.x, object.rotation.y, object.rotation.z));
    model = glm::translate(model, object.position);
    model = glm::scale(model, object.scale);

    object.program->variable("model") = model;
    object.program->variable("view") = camera.view();
    object.program->variable("projection") = camera.projection();
}

template<typename T>
void draw_call(T &object)
{
    glBindVertexArray(object.geometry->vao());
    glDrawArrays(GL_TRIANGLES, 0, object.geometry->vertex_count());
    glBindVertexArray(0);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    LOG_INFO() << "GLFW initialized with OpenGL 3.3 CORE PROFILE" << std::endl;
    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ein", NULL, NULL);
    if (window == NULL)
    {
        LOG_ERROR() << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwGetCursorPos(window, &last_mouse_pos.x, &last_mouse_pos.y);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    LOG_INFO() << "GLFW window created" << std::endl;

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        LOG_ERROR() << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    LOG_INFO() << "GLAD initialized" << std::endl;

    Shader_program::pointer pr1(new Shader_program(
            {std::make_shared<Shader>(Utils::load_text("/home/nikolay/Ein/Resources/Shaders/default.vert"),
                                      GL_VERTEX_SHADER),
             std::make_shared<Shader>(Utils::load_text("/home/nikolay/Ein/Resources/Shaders/default.frag"),
                                      GL_FRAGMENT_SHADER)}));
    Shader_program::pointer pr2(new Shader_program(
            {std::make_shared<Shader>(Utils::load_text("/home/nikolay/Ein/Resources/Shaders/lightsource.vert"),
                                      GL_VERTEX_SHADER),
             std::make_shared<Shader>(Utils::load_text("/home/nikolay/Ein/Resources/Shaders/lightsource.frag"),
                                      GL_FRAGMENT_SHADER)}));

    // ----------------------------------------------------------
    //      position             normal              tex_coord
    Geometry::pointer geom(new Geometry(
            {
                    {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f,  -1.0f}, {0.0f, 0.0f}},
                    {{0.5f,  -0.5f, -0.5f}, {0.0f,  0.0f,  -1.0f}, {1.0f, 0.0f}},
                    {{0.5f,  0.5f,  -0.5f}, {0.0f,  0.0f,  -1.0f}, {1.0f, 1.0f}},
                    {{0.5f,  0.5f,  -0.5f}, {0.0f,  0.0f,  -1.0f}, {1.0f, 1.0f}},
                    {{-0.5f, 0.5f,  -0.5f}, {0.0f,  0.0f,  -1.0f}, {0.0f, 1.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f,  -1.0f}, {0.0f, 0.0f}},
                    {{-0.5f, -0.5f, 0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f}},
                    {{0.5f,  -0.5f, 0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 0.0f}},
                    {{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f}},
                    {{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f}},
                    {{-0.5f, 0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f, 1.0f}},
                    {{-0.5f, -0.5f, 0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f}},
                    {{-0.5f, 0.5f,  0.5f},  {-1.0f, 0.0f,  0.0f},  {1.0f, 0.0f}},
                    {{-0.5f, 0.5f,  -0.5f}, {-1.0f, 0.0f,  0.0f},  {1.0f, 1.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f,  0.0f},  {0.0f, 1.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f,  0.0f},  {0.0f, 1.0f}},
                    {{-0.5f, -0.5f, 0.5f},  {-1.0f, 0.0f,  0.0f},  {0.0f, 0.0f}},
                    {{-0.5f, 0.5f,  0.5f},  {-1.0f, 0.0f,  0.0f},  {1.0f, 0.0f}},
                    {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
                    {{0.5f,  0.5f,  -0.5f}, {1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
                    {{0.5f,  -0.5f, -0.5f}, {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
                    {{0.5f,  -0.5f, -0.5f}, {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
                    {{0.5f,  -0.5f, 0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
                    {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {0.0f,  -1.0f, 0.0f},  {0.0f, 1.0f}},
                    {{0.5f,  -0.5f, -0.5f}, {0.0f,  -1.0f, 0.0f},  {1.0f, 1.0f}},
                    {{0.5f,  -0.5f, 0.5f},  {0.0f,  -1.0f, 0.0f},  {1.0f, 0.0f}},
                    {{0.5f,  -0.5f, 0.5f},  {0.0f,  -1.0f, 0.0f},  {1.0f, 0.0f}},
                    {{-0.5f, -0.5f, 0.5f},  {0.0f,  -1.0f, 0.0f},  {0.0f, 0.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {0.0f,  -1.0f, 0.0f},  {0.0f, 1.0f}},
                    {{-0.5f, 0.5f,  -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
                    {{0.5f,  0.5f,  -0.5f}, {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f}},
                    {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
                    {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
                    {{-0.5f, 0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f}},
                    {{-0.5f, 0.5f,  -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}}
            }));


    auto image = Utils::load_image("/home/nikolay/Ein/Resources/Textures/container2.png");
    Texture::pointer diffuse = std::make_shared<Texture>(image);
    Utils::free_image(image);

    auto image2 = Utils::load_image("/home/nikolay/Ein/Resources/Textures/container2_specular.png");
    Texture::pointer specular = std::make_shared<Texture>(image2);
    Utils::free_image(image2);

    Object obj;
    obj.diffuse = diffuse;
    obj.specular = specular;
    obj.geometry = geom;
    obj.program = pr1;

    Light_source point_light;
    point_light.geometry = geom;
    point_light.position = {1.0f, 0.7f, -7.0f};
    point_light.color = {0.5, 0.7, 0.7};
    point_light.program = pr2;

    glEnable(GL_DEPTH_TEST);

    auto draw_light = [](Light_source &source) {
        glUseProgram(source.program->id());
        export_common_data(source);
        source.program->variable("light_color") = source.color;
        draw_call(source);
    };

    auto draw_object = [](Object &object, Light_source &source) {
        glUseProgram(object.program->id());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, object.diffuse->id());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, object.specular->id());

        export_common_data(object);
        object.program->variable("camera_position") = camera.position();
        object.program->variable("ambient") = ambient;
        object.program->variable("light.color") = source.color;
        object.program->variable("light.position") = source.position;

        draw_call(object);
    };

    glUseProgram(obj.program->id());
    obj.program->variable("diffuse_map") = 0;
    obj.program->variable("specular_map") = 1;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        process_input(window);

        // render
        // ------

        glClearColor(ambient.r, ambient.r, ambient.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw_light(point_light);
        draw_object(obj, point_light);

        // you spin me right round!
        point_light.position = {4*sin(glfwGetTime()), 4*sin(0.5*glfwGetTime()), cos(glfwGetTime())};
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();


    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window)
{

    float curr_timestamp = glfwGetTime();
    float dt = curr_timestamp - last_timestamp;
    last_timestamp = curr_timestamp;


    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.move(Camera::Direction::forward, dt);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.move(Camera::Direction::backward, dt);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.move(Camera::Direction::left, dt);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.move(Camera::Direction::right, dt);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.move(Camera::Direction::up, dt);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        camera.move(Camera::Direction::down, dt);
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) noexcept
{
    if (!first)
    {
        camera.rotate((xpos - last_mouse_pos.x) * 0.25, -(ypos - last_mouse_pos.y) * 0.25);
    }

    last_mouse_pos.x = xpos;
    last_mouse_pos.y = ypos;
    first = false;
}
