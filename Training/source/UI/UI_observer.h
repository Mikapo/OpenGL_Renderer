#pragma once
#include "UI_data.h"
class UI_observer
{
public:
    virtual void on_button_event(UI_button_event type) = 0;
    virtual void on_combo_box_event(std::string input, UI_combo_box_event type) = 0;
};
