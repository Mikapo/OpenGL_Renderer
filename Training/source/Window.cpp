#include "Window.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include <iostream>



void Window::start()
{
    if (!has_started)
    {
        has_started = true;
        init();
        logic_thread_handle = std::thread([this] { logic_loop(); });
        render_loop();
        cleanup();
        has_started = false;
    }
}

void Window::stop() { has_started = false; }

Dimensions Window::get_window_dimensions() const
{ 
    Dimensions dimensions; 
    if (has_started && window)
        glfwGetWindowSize(window, &dimensions.width, &dimensions.height);
    return dimensions;
}

float Window::get_delta_seconds() const
{
    return deltatime;
}

void Window::init() 
{
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 1000, name.c_str(), NULL, NULL);
    glfwSetWindowSizeLimits(window, 1000, 1000, 1000, 1000);

    if (!window)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);
    update_deltatime();
    glfwSetWindowUserPointer(get_window(), this);
    setup_callbacks();
    logic_thread_exit_flag = false;
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
}

void Window::update_deltatime()
{
    using namespace std::chrono;

    auto time = high_resolution_clock::now();
    auto time_passed = time - time_since_last_frame;
    time_since_last_frame = time;
    deltatime = time_passed.count() * 0.000000001f;
}


void Window::logic_loop()
{
    using namespace std::chrono;

    time_point<system_clock> frame_time = system_clock::now();
    while (!logic_thread_exit_flag)
    {
        frame_time += milliseconds(1000 / 60);
        input_handler.update();
        update_deltatime();
        update(deltatime);

        //limit each logic thread frame to 60fps per second
        std::this_thread::sleep_until(frame_time);
    }
}

void Window::render_loop() const
{
    while (!glfwWindowShouldClose(window) && has_started)
    {
        glDepthMask(GL_TRUE);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(background_color.R, background_color.B, background_color.G, background_color.A);
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::cleanup()
{
    logic_thread_exit_flag = true;
    logic_thread_handle.join();
    glfwTerminate();
    window = nullptr;
}