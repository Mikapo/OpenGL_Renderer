#pragma once

#include "Slider.h"

class Slider_angle : public Slider
{
public:
	Slider_angle(const std::string& name) : Slider(name) 
	{
		m_format = "%.0f deg";
	}

	void render() override;
};

