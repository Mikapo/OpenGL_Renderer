#pragma once

#include "UI_element_notify.h"

#include <array>
#include <glm/vec4.hpp>

class Color_picker : public UI_element_notify<glm::vec4>
{
public:
	Color_picker(const std::string& name) : UI_element_notify(name) {}

	void render() override;
	void check_for_events() override;

private:
	std::array<float, 4> current_color = {0.0f, 0.0f, 0.0f, 1.0f};
	std::array<float, 4> last_checked_color = {0.0f, 0.0f, 0.0f, 1.0f};

};

