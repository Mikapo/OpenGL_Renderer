#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include "UI_data.h"
#include "Elements/Button.h"

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

    std::unordered_set<UI_observer*> m_observers;
    std::vector<std::unique_ptr<UI_element>> m_elements;
    bool m_hovered_by_mouse = false;
};
