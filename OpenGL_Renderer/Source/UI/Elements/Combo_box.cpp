#include "Combo_box.h"

void Combo_box::render()
{
    if (ImGui::BeginCombo(get_name().c_str(), m_current_item.c_str()))
    {
        for (std::string item : m_items)
        {
            bool is_selected = (m_current_item == item);
            if (ImGui::Selectable(item.c_str(), is_selected))
                if (m_current_item != item.c_str())
                {
                    m_current_item = item.c_str();
                }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}

void Combo_box::check_for_events()
{
    if (m_current_item != m_last_checked_item)
    {
        notify(m_current_item);
        m_last_checked_item = m_current_item;
    }
}

void Combo_box::add_item(const std::string& new_item)
{
    m_items.emplace_back(new_item);
}

void Combo_box::set_current_item_index(unsigned int index)
{
    if (index > m_items.size())
        throw 1; // out of bounds

    const std::string& item = m_items[index];
    m_current_item = item;
    m_last_checked_item = item;
}
