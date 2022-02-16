#pragma once

#include "UI/Elements/UI_element_notify.h"

class Slider : public UI_element_notify<float>
{
public:
	Slider(const std::string& name) : UI_element_notify(name) {}

	void check_for_events() final;
	void set_max(float max) { m_max = max; }
	void set_min(float min) { m_min = min; }
	void set_format(const std::string& format) { m_format = format; }
	void set_value(float value) { m_current_value = value; }

protected:
	float m_max = 360.f, m_min = -360.0f;
	std::string m_format = "%.0f";
	float m_current_value = 0.0f;

private:
	float m_last_checked_value = 0.0f;
};

