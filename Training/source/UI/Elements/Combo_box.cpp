#include "Combo_box.h"

void Combo_box::update()
{
    if (ImGui::BeginCombo(m_name.c_str(), m_current_item.c_str()))
    {
        for (std::string item : m_items)
        {
            bool is_selected = (m_current_item == item);
            if (ImGui::Selectable(item.c_str(), is_selected))
                if (m_current_item != item.c_str())
                {
                    m_current_item = item.c_str();
                    for (UI_observer* observer : m_observers)
                        observer->on_combo_box_event(m_current_item, m_ui_event);
                }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}
