#pragma once

#include "UI_observer.h"

class Pathfinding_window;
class UI_event_handler : public UI_observer
{
public:
    UI_event_handler(Pathfinding_window* owner);

    void on_button_event(UI_button_event type) override;
    void on_combo_box_event(std::string input, UI_combo_box_event type) override;

private:
    Pathfinding_window* owner = nullptr;

};
