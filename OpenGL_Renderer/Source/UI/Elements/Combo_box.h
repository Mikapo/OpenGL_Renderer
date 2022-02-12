#pragma once

#include <initializer_list>
#include <string>
#include <vector>

#include "UI_element.h"

class Combo_box : public UI_element
{
public:
    Combo_box(std::string name, UI_combo_box_event ui_event, std::initializer_list<std::string> items) : m_name(name), m_ui_event(ui_event), m_items(items)
    {
        if (items.size() > 0)
            m_current_item = items.begin()->c_str();
    }

    void update() override;

private:
    UI_combo_box_event m_ui_event;
    std::vector<std::string> m_items;
    std::string m_current_item;
    std::string m_name;
};
