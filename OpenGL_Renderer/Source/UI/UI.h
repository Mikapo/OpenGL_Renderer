#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "UI/Elements/UI_element.h"

struct GLFWwindow;
class UI
{
public:
    UI(const std::string& name) : m_name(name) {}

    void render();
    void check_for_events();
    void add_window_flags(ImGuiWindowFlags window_flag);
    
    template<typename T>
    T* add_chidren(const std::string& name)
    {
        m_elements.emplace_back(new T(name));
        return dynamic_cast<T*>(m_elements.back().get());
    }

    bool is_hovered_by_mouse() const;

private:
    void render_elements();

    ImGuiWindowFlags m_window_flags = 0;
    std::string m_name;
    std::vector<std::unique_ptr<UI_element>> m_elements;
    bool m_hovered_by_mouse = false;
    bool m_is_open = true;
};
