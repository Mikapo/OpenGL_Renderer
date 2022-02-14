#include "Child_window.h"

void Child_window::render()
{
	ImGui::BeginChild(m_id, { m_width, m_height }, m_has_border);
	render_children();
	ImGui::EndChild();
}
