#pragma once

#include "UI_element_parent.h"

class Child_window : public UI_element_parent
{
public:
	Child_window(const std::string& name) : UI_element_parent(name) {}

	void render() override;

	void set_border(bool border) { m_has_border = border; }
	void set_id(int new_id) { m_id = new_id; }
	void set_size(float width, float height) { m_width = width; m_height = height; }

private:
	float m_width = 0, m_height = 0;
	bool m_has_border = false;
	int m_id = 1;
};

