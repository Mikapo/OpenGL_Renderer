#pragma once

#include <initializer_list>
#include <string>
#include <vector>

#include "UI_element.h"

class Combo_box : public UI_element
{
public:
    Combo_box(std::string name, UI_combo_box_event ui_event, std::initializer_list<std::string> items) : name(name), ui_event(ui_event), items(items)
    {
        if (items.size() > 0)
            current_item = items.begin()->c_str();
    }

    void update() override;

private:
    UI_combo_box_event ui_event;
    std::vector<std::string> items;
    std::string current_item;
    std::string name;
};
