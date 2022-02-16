#include "Collapsing_header.h"

void Collapsing_header::render()
{
	if (ImGui::CollapsingHeader(get_name().c_str()))
	{
		render_children();
	}
}
