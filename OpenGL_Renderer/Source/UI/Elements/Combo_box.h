#pragma once

#include "UI_element_notify.h"

#include <initializer_list>
#include <string>
#include <vector>

class Combo_box : public UI_element_notify<const std::string&>
{
public:
    Combo_box(std::string name) : UI_element_notify(name) {}

    void render() override;
    void check_for_events() override;
    void add_item(const std::string& new_item);
    void set_current_item_index(unsigned int index);

private:
    std::vector<std::string> m_items;
    std::string m_current_item;
    std::string m_last_checked_item;
};
