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
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(background_color.R, background_color.B, background_color.G, background_color.A);
        update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
