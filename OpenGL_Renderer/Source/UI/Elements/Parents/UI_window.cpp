#include "UI_window.h"

void UI_window::render()
{
    ImGui::Begin(get_name().c_str(), &m_is_open, m_flags);
    m_hovered_by_mouse = ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered();

    if (m_needs_resize)
    {
        ImGui::SetWindowSize({ m_resize_width, m_resize_height });
        m_needs_resize = false;
    }

    render_children();
    ImGui::End();
}

void UI_window::add_flag(ImGuiWindowFlags flag)
{
    m_flags |= flag;
}

void UI_window::resize(float width, float height)
{
    m_resize_width = width;
    m_resize_height = height;
    m_needs_resize = true;
}
