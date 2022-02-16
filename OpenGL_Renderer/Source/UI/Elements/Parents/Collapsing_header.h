#pragma once

#include "UI_element_parent.h"

class Collapsing_header : public UI_element_parent
{
public:
	Collapsing_header(const std::string& name) : UI_element_parent(name) {}

	void render() override;

};

