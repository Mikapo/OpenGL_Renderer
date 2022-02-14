#pragma once

#include "UI_element_notify.h"

class Checkbox : public UI_element_notify<bool>
{
public:
	Checkbox(const std::string& name) : UI_element_notify(name) {}

	void render() override;
	void check_for_events() override;

private:
	bool m_checked = true;
	bool m_last_checked = true;
};

