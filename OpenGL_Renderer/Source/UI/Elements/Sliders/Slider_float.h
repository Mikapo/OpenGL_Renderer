#pragma once

#include "Slider.h"

class Slider_float : public Slider
{
public:
	Slider_float(const std::string& name) : Slider(name) {}

	void render() override;
};

