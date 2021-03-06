#pragma once

#include "UI/Elements/UI_element.h"

class UI_element_parent : public UI_element
{
public:
	UI_element_parent(const std::string& name) : UI_element(name) {}

	template<typename T>
	T* add_children(const std::string& name)
	{
		children.emplace_back(new T(name));
		return dynamic_cast<T*>(children.back().get());
	}

	void check_for_events() final;

protected:
	void render_children();
	
private:
	std::vector<std::unique_ptr<UI_element>> children;
};

