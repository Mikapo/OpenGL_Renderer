#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "texture.h"

class Texture_factory
{
public:
	static std::shared_ptr<Texture> get(const std::string& path);

private:
	static std::unordered_map<std::string, std::weak_ptr<Texture>> texture_cache;
};

