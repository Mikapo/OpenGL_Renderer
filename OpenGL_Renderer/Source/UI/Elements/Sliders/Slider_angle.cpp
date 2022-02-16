#include "Slider_angle.h"

void Slider_angle::render()
{
	ImGui::SliderAngle(get_name().c_str(), &m_current_value, m_min, m_max, m_format.c_str());
}

