#include "Button.h"

void Button::update()
{
    if (ImGui::Button(m_name.c_str()))
    {
        for (auto observer : m_observers)
            observer->on_button_event(m_button_event_on_clicked);
    }
}
