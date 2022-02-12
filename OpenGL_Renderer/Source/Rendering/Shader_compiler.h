#pragma once

#include "Rendering/Shader.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "Object/Light.h"

class Shader_compiler
{
public:
	static std::shared_ptr<Shader> get(const std::string& frag_path, const std::string& vert_path);
	static std::unordered_map<std::string, std::weak_ptr<Shader>> get_current_shaders() { return m_shader_cache; }

private:
	static std::unordered_map<std::string, std::weak_ptr<Shader>> m_shader_cache;
};

