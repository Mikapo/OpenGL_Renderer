#include "Button.h"

void Button::render()
{
    m_clicked = ImGui::Button(get_name().c_str());
}

void Button::check_for_events()
{
    if (m_clicked != m_last_checked_status)
    {
        if(m_clicked)
            notify();
        m_last_checked_status = m_clicked;
    }
}

