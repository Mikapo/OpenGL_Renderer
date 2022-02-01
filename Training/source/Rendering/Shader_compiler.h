#pragma once

#include "Shader.h"
#include <memory>
#include <string>
#include <unordered_map>

class Shader_compiler
{
public:
	static std::shared_ptr<Shader> get(const std::string& frag_path, const std::string& vert_path);

private:
	static std::unordered_map<std::string, std::weak_ptr<Shader>> shader_cache;
};

