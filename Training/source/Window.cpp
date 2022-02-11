#include "Window.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>


void Window::start()
{
    if (!m_has_started)
    {
        m_has_started = true;
        init();
        m_logic_thread_handle = std::thread([this] { logic_loop(); });
        render_loop();
        cleanup();
        m_has_started = false;
    }
}

void Window::stop() { m_has_started = false; }

Dimensions Window::get_window_dimensions() const
{ 
    Dimensions dimensions; 
    if (m_has_started && m_window)
        glfwGetWindowSize(m_window, &dimensions.m_width, &dimensions.m_height);
    return dimensions;
}

float Window::get_delta_seconds() const
{
    return m_deltatime;
}

void Window::init() 
{
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(1000, 1000, m_name.c_str(), NULL, NULL);
    glfwSetWindowSizeLimits(m_window, 1000, 1000, 1000, 1000);

    if (!m_window)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);
    update_deltatime();
    glfwSetWindowUserPointer(get_window(), this);
    setup_callbacks();
    m_logic_thread_exit_flag = false;
}

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* msg, const void* data)
{
    std::string _source;
    std::string _type;
    std::string _severity;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

    default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

    default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

    default:
        _severity = "UNKNOWN";
        break;
    }

    std::cout << "----------OpenGL Debug message----------\n";
    std::cout << "from: " << _source << "\n";
    std::cout << "type: " << _type << "\n";
    std::cout << "severity: " << _severity << "\n";
    std::cout << "message: " << msg << "\n";
    std::cout << "----------------------------------------\n\n";
}

void Window::setup_callbacks()
{
    auto on_key = [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
            static_cast<Window*>(glfwGetWindowUserPointer(window))->input_handler.on_key_event(key, action);

        else if (action == GLFW_RELEASE)
            static_cast<Window*>(glfwGetWindowUserPointer(window))->input_handler.on_key_event(key, action);

    };
    glfwSetKeyCallback(get_window(), on_key);

    auto on_resize = [](GLFWwindow* window, int new_width, int new_height)
    {
        static_cast<Window*>(glfwGetWindowUserPointer(window))->on_window_resize(window, new_width, new_height);
    };
    glfwSetWindowSizeCallback(get_window(), on_resize);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);
}

void Window::update_deltatime()
{
    using namespace std::chrono;

    auto time = high_resolution_clock::now();
    auto time_passed = time - m_time_since_last_frame;
    m_time_since_last_frame = time;
    m_deltatime = time_passed.count() * 0.000000001f;
}

void Window::logic_loop()
{
    using namespace std::chrono;

    time_point<system_clock> frame_time = system_clock::now();
    while (!m_logic_thread_exit_flag)
    {
        frame_time += milliseconds(1000 / 60);
        input_handler.update();
        update_deltatime();
        update(m_deltatime);

        //limit each logic thread frame to 60fps per second
        std::this_thread::sleep_until(frame_time);
    }
}

void Window::render_loop() const
{
    while (!glfwWindowShouldClose(m_window) && m_has_started)
    {
        glDepthMask(GL_TRUE);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(m_background_color.R, m_background_color.B, m_background_color.G, m_background_color.A);
        render();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Window::cleanup()
{
    m_logic_thread_exit_flag = true;
    m_logic_thread_handle.join();
    glfwTerminate();
    m_window = nullptr;
}