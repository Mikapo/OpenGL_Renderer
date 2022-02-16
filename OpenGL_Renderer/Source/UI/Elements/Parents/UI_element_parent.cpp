#include "UI_element_parent.h"

void UI_element_parent::render_children()
{
	for (auto& child : children)
		child->render();
}

void UI_element_parent::check_for_events()
{
	for (auto& child : children)
		child->check_for_events();
}
