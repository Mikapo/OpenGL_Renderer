#include "Slider.h"

void Slider::check_for_events()
{
	if (m_current_value != m_last_checked_value)
	{
		notify(m_current_value);
		m_last_checked_value = m_current_value;
	}
}
