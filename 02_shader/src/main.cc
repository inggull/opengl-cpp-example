#include <spdlog/spdlog.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <common.hh>
#include <Shader.hh>

#define WINDOW_NAME "Shader"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void onFramebufferSizeEvent(GLFWwindow* window, int width, int height);
void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    // Initialize glfw
    SPDLOG_INFO("Initialize glfw");
    if (glfwInit() == GLFW_FALSE) {
        SPDLOG_ERROR("Failed to initialize glfw");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create glfw window
    SPDLOG_INFO("Create glfw window");
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (window == NULL) {
        SPDLOG_ERROR("Failed to create glfw window");
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize glad
    SPDLOG_INFO("Initialize glad");
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        SPDLOG_ERROR("Failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    auto gl_version = glGetString(GL_VERSION);
    SPDLOG_INFO("Loaded OpenGL {}", reinterpret_cast<const char*>(gl_version));
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // State-setting function
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // State-setting function

    auto vertex_shader = Shader::create("shader/simple.vert", GL_VERTEX_SHADER);
    if (vertex_shader.has_value() == false) {
        SPDLOG_ERROR(vertex_shader.error());
        return -1;
    }
    auto fragment_shader = Shader::create("shader/simple.frag", GL_FRAGMENT_SHADER);
    if (fragment_shader.has_value() == false) {
        SPDLOG_ERROR(fragment_shader.error());
        return -1;
    }
    SPDLOG_INFO("Created vertex shader({})", vertex_shader.value()->get());
    SPDLOG_INFO("Created fragment shader({})", fragment_shader.value()->get());

    glfwSetFramebufferSizeCallback(window, onFramebufferSizeEvent);
    glfwSetKeyCallback(window, onKeyEvent);

    // Strat main loop
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT); // State-using function
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void onFramebufferSizeEvent(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("FramebufferSize changed: {} x {}", width, height);
    glViewport(0, 0, width, height);
}

void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Press" :
        action == GLFW_RELEASE ? "Release" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        ((mods & GLFW_MOD_CONTROL) ? "C" : "-"),
        ((mods & GLFW_MOD_SHIFT) ? "S" : "-"),
        ((mods & GLFW_MOD_ALT) ? "A" : "-")
    );

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}