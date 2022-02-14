#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <memory>
#include <string>
#include <unordered_map>

class UI_element
{
public:
    UI_element(const std::string& name) : m_name(name) {}

    virtual void render() = 0;
    virtual void check_for_events() = 0;

    std::string get_name() const { return m_name; }

private:
    std::string m_name;
   
};
