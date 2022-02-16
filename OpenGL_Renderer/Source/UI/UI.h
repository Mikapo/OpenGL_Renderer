#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "UI/Elements/Parents/UI_window.h"

struct GLFWwindow;
class UI
{
public:
    UI(const std::string& name) : m_name(name) {}

    static void init(GLFWwindow* window);
    static void cleanup();
    void render();
    void check_for_events();
    UI_window* add_window(const std::string& name);
    bool is_hovered_by_mouse() const;

private:
    void render_windows();

    ImGuiWindowFlags m_window_flags = 0;
    std::string m_name;
    std::vector<std::unique_ptr<UI_window>> m_windows;
    bool m_hovered_by_mouse = false;
    bool m_is_open = true;
};
