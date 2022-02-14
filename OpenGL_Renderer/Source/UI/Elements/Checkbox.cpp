#include "Checkbox.h"

void Checkbox::render()
{
	ImGui::Checkbox(get_name().c_str(), &m_checked);
}

void Checkbox::check_for_events()
{
	if (m_checked != m_last_checked)
	{
		notify(m_checked);
		m_last_checked = m_checked;
	}

}
