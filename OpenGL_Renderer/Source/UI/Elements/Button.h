#pragma once

#include "UI/UI_data.h"
#include "UI_element.h"

#include <string>

class Button : public UI_element
{
public:
    Button(std::string name, UI_button_event button_event_on_clicked)
        : m_name(name), m_button_event_on_clicked(button_event_on_clicked)
    {
    }

    void update() override;

private:
    std::string m_name;
    UI_button_event m_button_event_on_clicked;
};
