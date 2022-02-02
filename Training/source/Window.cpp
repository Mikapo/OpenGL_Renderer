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

    if (!window)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);
    update_deltatime();
    glfwSetWindowUserPointer(get_window(), this);

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

void Window::cleanup() 
{ 
    glfwTerminate(); 
    window = nullptr;
}

void Window::render_loop() 
{
    while (!glfwWindowShouldClose(window) && has_started)
    {
        glDepthMask(GL_TRUE);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(background_color.R, background_color.B, background_color.G, background_color.A);
        input_handler.update();
        update_deltatime();
        update(deltatime);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::update_deltatime()
{
    auto time = std::chrono::high_resolution_clock::now();
    auto time_passed = time - time_since_last_frame;
    time_since_last_frame = time;
    deltatime = time_passed.count() * 0.000000001;
}
