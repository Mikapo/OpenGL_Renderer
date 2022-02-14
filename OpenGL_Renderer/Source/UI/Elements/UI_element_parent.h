#pragma once

#include "UI_element.h"

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

protected:
	void render_children();
	
private:
	void check_for_events() final;

	std::vector<std::unique_ptr<UI_element>> children;


};

