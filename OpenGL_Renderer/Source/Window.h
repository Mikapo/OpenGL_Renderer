#pragma once

#include <chrono>
#include <glew.h>
#include <glm/vec4.hpp>
#include <string>
#include <thread>

#include "Dimensions.h"
#include "Input_handler.h"



struct GLFWwindow;
class Window
{
public:
    using super = Window;

    Window(const std::string& window_name, int width, int height) : m_name(window_name), m_width(width), m_height(height) {}
    void start();
    void stop();
    void set_background_color(float R, float G, float B, float A) { m_background_color = {R, G, B, A}; }
    void set_debug_messages_enabled(bool enabled);

    inline GLFWwindow* get_window() const { return m_window; }
    Dimensions get_window_dimensions() const;
    float get_delta_seconds() const;
    void(APIENTRY* DEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

    virtual void on_window_resize(GLFWwindow* window, int new_width, int new_height) {};
    void logic_loop();

    void setup_callbacks() const;

protected:
    virtual void init();
    virtual void cleanup();
    virtual void update(float deltatime) {};
    virtual void render() {};
    Input_handler* get_input_hanlder() { return &m_input_handler; }

private:
    void render_loop();
    void update_deltatime();

    std::string m_name;
    int m_width, m_height;
    GLFWwindow* m_window = nullptr;
    bool m_has_started = false;
    glm::vec4 m_background_color = {0.0f, 0.0f, 0.0f, 0.0f};
    std::chrono::steady_clock::time_point m_time_since_last_frame;
    float m_deltatime = 0.0f;
    Input_handler m_input_handler;

    std::thread m_logic_thread_handle;
    bool m_logic_thread_exit_flag = true;
};
