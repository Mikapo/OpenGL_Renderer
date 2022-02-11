#pragma once

#include <chrono>
#include <glew.h>
#include <string>
#include <thread>

#include "Dimensions.h"
#include "Input_handler.h"


struct Color
{
    float R;
    float G;
    float B;
    float A;
};


struct GLFWwindow;
class Window
{
public:
    using super = Window;

    Window(const std::string& window_name) : m_name(window_name) {}
    void start();
    void stop();
    void set_background_color(float R, float G, float B, float A) { m_background_color = {R, G, B, A}; }
    inline GLFWwindow* get_window() const { return m_window; }
    Dimensions get_window_dimensions() const;
    float get_delta_seconds() const;
    void(APIENTRY* DEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

    virtual void on_window_resize(GLFWwindow* window, int new_width, int new_height) {};
    void logic_loop();

    void setup_callbacks();

protected:
    virtual void init();
    virtual void cleanup();
    virtual void update(float deltatime) {};
    virtual void render() const {};

    Input_handler input_handler;

private:
    void render_loop() const;
    void update_deltatime();

    GLFWwindow* m_window = nullptr;
    std::string m_name;
    bool m_has_started = false;
    Color m_background_color;
    std::chrono::steady_clock::time_point m_time_since_last_frame;
    float m_deltatime;

    std::thread m_logic_thread_handle;
    bool m_logic_thread_exit_flag = true;
};
