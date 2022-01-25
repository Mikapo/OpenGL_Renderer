#include "UI.h"

#include "UI_observer.h"
#include "Elements/Combo_box.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void UI::init(GLFWwindow* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    setup_elements();
}

void UI::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Pathfinder");
    hovered_by_mouse = ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered();
    update_elements();
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::add_observer(UI_observer* obs)
{
    for (const auto& element : elements)
        element->add_observer(obs);
}

void UI::remove_observer(UI_observer* obs)
{
    for (const auto& element : elements)
        element->remove_observer(obs);
}

bool UI::is_hovered_by_mouse() const 
{ return hovered_by_mouse; }

void UI::setup_elements()
{
    elements.emplace_back(new Button("start", UI_button_event::start_button_pressed));
    elements.emplace_back(new Button("stop", UI_button_event::stop_button_pressed));
    elements.emplace_back(new Combo_box("Algorimth", UI_combo_box_event::algorimth, {"Breadth first search", "Dijkstras"}));
    elements.emplace_back(new Combo_box("Draw mode", UI_combo_box_event::draw_mode, {"Clear", "Wall", "Goal", "Start"}));
}

void UI::update_elements()
{
    for (const auto& element : elements)
        element->update();
}
