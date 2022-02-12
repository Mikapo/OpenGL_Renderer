#pragma once

#include "UI/UI_observer.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <unordered_set>

class UI_element
{
public:
    virtual void update() = 0;
    void add_observer(UI_observer* observer) { m_observers.insert(observer); }
    void remove_observer(UI_observer* observer) { m_observers.erase(observer); }

protected:
    std::unordered_set<UI_observer*> m_observers;
};
