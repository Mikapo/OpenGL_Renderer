#pragma once

#include "Dimensions.h"

#include <string>
#include <chrono>

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

protected:
    virtual void update(double deltatime) = 0;
    virtual void init();
    virtual void cleanup();

private:
    void render_loop();
    double get_deltatime();

    GLFWwindow* window = nullptr;
    std::string name;
    bool has_started = false;
    Color background_color;
    std::chrono::steady_clock::time_point time_since_last_frame;
    
};
