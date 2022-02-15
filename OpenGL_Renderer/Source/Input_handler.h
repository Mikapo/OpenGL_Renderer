#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

struct Axis_mapping
{
public:
	virtual void call(float value) = 0;

	void add_key(int key, float value)
	{
		m_keys[key] = value;
	}

	float get_current_value() const { return m_current_value; }
	void set_current_value(float value) { m_current_value = value; }
	int get_current_key() const { return m_current_key; }
	void set_current_key(int new_key) { m_current_key = new_key; }
	const std::unordered_map<int, float>& get_keys() const { return m_keys; }

private:

	float m_current_value = 0;
	int m_current_key = 0;
	std::unordered_map<int, float> m_keys;
};

template<typename T>
struct Axis_mapping_function : public Axis_mapping
{
public:
	Axis_mapping_function(T* obj, void (T::*f)(float)) 
		: m_obj(obj), m_f(f) {}

	void call(float value) override
	{
		(m_obj->*m_f)(value);
	}

private:
	T* m_obj;
	void (T::*m_f)(float);
};


class Input_handler
{
public:
	void update()
	{
		for (auto& value : m_axis_mappings)
		{
			auto* mapping = value.second.get();
			mapping->call(mapping->get_current_value());
		}
	}

	void on_key_event(int key, int event)
	{
		for (auto& value : m_axis_mappings)
		{
			auto* mapping = value.second.get();

			if (event == GLFW_RELEASE && key == mapping->get_current_key())
				mapping->set_current_value(0.0f);

			else if (event == GLFW_PRESS && mapping->get_keys().contains(key))
			{
				mapping->set_current_value(mapping->get_keys().at(key));
				mapping->set_current_key(key);
			}
		}
	}

	template<typename T>
	Axis_mapping* add_axis_mapping(const std::string& name, T* obj, void (T::* f)(float))
	{
		m_axis_mappings.emplace(name, new Axis_mapping_function(obj, f));
		return m_axis_mappings[name].get();
	}

	void remove_axis_mapping(const std::string& name)
	{
		m_axis_mappings.erase(name);
	}

	void clear()
	{

	}

private:
	std::unordered_map<std::string, std::unique_ptr<Axis_mapping>> m_axis_mappings;
};

