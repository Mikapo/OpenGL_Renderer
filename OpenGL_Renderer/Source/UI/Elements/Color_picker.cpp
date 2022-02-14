#include "Color_picker.h"

void Color_picker::render()
{
	ImGui::ColorPicker4(get_name().c_str(), current_color);
}

void Color_picker::check_for_events()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (current_color[i] != last_checked_color[i])
		{
			notify(glm::vec4(current_color[0], current_color[1], current_color[2], current_color[3]));

			for (size_t i = 0; i < 4; i++)
				last_checked_color[i] = current_color[i];

			break;
		}
	}
}
