#include "Window.h"

#include "glew.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

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
    get_deltatime();
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
        update(get_deltatime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

double Window::get_deltatime()
{
    auto time = std::chrono::high_resolution_clock::now();
    auto time_passed = time - time_since_last_frame;
    time_since_last_frame = time;
    return time_passed.count() * 0.000000001;
}
