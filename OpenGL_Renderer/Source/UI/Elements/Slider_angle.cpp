#include "Slider_angle.h"

void Slider_angle::render()
{
	ImGui::SliderAngle(get_name().c_str(), &m_current_value);
}

void Slider_angle::check_for_events()
{
	if (m_current_value != m_last_checked_value)
	{
		notify(m_current_value);
		m_last_checked_value = m_current_value;
	}
}
