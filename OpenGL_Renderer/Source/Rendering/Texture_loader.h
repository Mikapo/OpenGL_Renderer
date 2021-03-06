#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "texture.h"

class Texture_loader
{
public:
	static std::shared_ptr<Texture> load(const std::string& path);

private:
	static std::unordered_map<std::string, std::weak_ptr<Texture>> m_texture_cache;
};

