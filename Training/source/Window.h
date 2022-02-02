#pragma once

#include "Dimensions.h"

#include "glew.h"
#include <string>
#include <chrono>
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

    Window(const std::string& window_name) : name(window_name) {}
    void start();
    void stop();
    void set_background_color(float R, float G, float B, float A) { background_color = {R, G, B, A}; }
    inline GLFWwindow* get_window() const { return window; }
    Dimensions get_window_dimensions() const;
    float get_delta_seconds() const;

    virtual void on_window_resize(GLFWwindow* window, int new_width, int new_height) {};

protected:
    virtual void update(float deltatime) {};
    virtual void init();
    virtual void cleanup();

    Input_handler input_handler;

private:
    void render_loop();
    void update_deltatime();

    GLFWwindow* window = nullptr;
    std::string name;
    bool has_started = false;
    Color background_color;
    std::chrono::steady_clock::time_point time_since_last_frame;
    float deltatime;
    
};
