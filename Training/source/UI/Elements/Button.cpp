#include "Button.h"

void Button::update()
{
    if (ImGui::Button(name.c_str()))
    {
        for (auto observer : observers)
            observer->on_button_event(button_event_on_clicked);
    }
}
