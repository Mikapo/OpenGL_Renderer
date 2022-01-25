#include "Combo_box.h"

void Combo_box::update()
{
    if (ImGui::BeginCombo(name.c_str(), current_item.c_str()))
    {
        for (std::string item : items)
        {
            bool is_selected = (current_item == item);
            if (ImGui::Selectable(item.c_str(), is_selected))
                if (current_item != item.c_str())
                {
                    current_item = item.c_str();
                    for (UI_observer* observer : observers)
                        observer->on_combo_box_event(current_item, ui_event);
                }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}
