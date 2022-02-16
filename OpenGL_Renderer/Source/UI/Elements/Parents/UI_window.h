#pragma once

#include "UI_element_parent.h"

class UI_window : public UI_element_parent
{
public:
	UI_window(const std::string& name) : UI_element_parent(name) {}

	void render() override;
	void add_flag(ImGuiWindowFlags flag);
	void resize(float width, float height);
	
private:
	bool m_is_open = true;
	bool m_hovered_by_mouse = false;

	bool m_needs_resize = false;
	float m_resize_width = 0.0f, m_resize_height = 0.0f;

	ImGuiWindowFlags m_flags = ImGuiWindowFlags_None;

};

