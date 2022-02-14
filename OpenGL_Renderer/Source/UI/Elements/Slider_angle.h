#pragma once

#include "UI_element_notify.h"

class Slider_angle : public UI_element_notify<float>
{
public:
	Slider_angle(const std::string& name) : UI_element_notify(name) {}

	void render() override;
	void check_for_events() override;

private:
	float m_current_value = 0.0f;
	float m_last_checked_value = 0.0f;
};

