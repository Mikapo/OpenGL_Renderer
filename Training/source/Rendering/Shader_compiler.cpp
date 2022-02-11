#include "Shader_compiler.h"

std::unordered_map<std::string, std::weak_ptr<Shader>> Shader_compiler::m_shader_cache;

std::shared_ptr<Shader> Shader_compiler::get(const std::string& frag_path, const std::string& vert_path)
{
	std::string combined = frag_path + vert_path;
	if (!m_shader_cache[combined].expired())
		return m_shader_cache[combined].lock();
	else
	{
		std::shared_ptr<Shader> temp = std::make_shared<Shader>(frag_path, vert_path);
		m_shader_cache[combined] = temp;
		return temp;
	}
}

