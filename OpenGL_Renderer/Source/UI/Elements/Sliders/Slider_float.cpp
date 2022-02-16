#include "Slider_float.h"

void Slider_float::render()
{
	ImGui::SliderFloat(get_name().c_str(), &m_current_value, m_min, m_max, m_format.c_str());
}
