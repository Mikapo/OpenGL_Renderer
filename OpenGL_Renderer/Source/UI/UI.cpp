#include "UI.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

void UI::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin(m_name.c_str(), &m_is_open, m_window_flags);
    m_hovered_by_mouse = ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered();
    render_elements();
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
   
}

void UI::render_elements()
{
    for (const auto& element : m_elements)
        element->render();
}

void UI::check_for_events()
{
    for (const auto& element : m_elements)
        element->check_for_events();
}

void UI::add_window_flags(ImGuiWindowFlags window_flag)
{
    m_window_flags |= window_flag;
}

bool UI::is_hovered_by_mouse() const 
{ 
    return m_hovered_by_mouse; 
}

