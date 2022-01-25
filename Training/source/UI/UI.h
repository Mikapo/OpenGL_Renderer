#pragma once

#include "UI_data.h"
#include"Elements/Button.h"

#include <unordered_set>
#include <vector>
#include <memory>

struct GLFWwindow;
class UI_observer;
class UI
{
public:
    void init(GLFWwindow* window);
    void cleanup();
    void update();
    void add_observer(UI_observer* obs);
    void remove_observer(UI_observer* obs);
    bool is_hovered_by_mouse() const;

private:
    void setup_elements();
    void update_elements();

    std::unordered_set<UI_observer*> observers;
    std::vector<std::unique_ptr<UI_element>> elements;
    bool hovered_by_mouse = false;
};
