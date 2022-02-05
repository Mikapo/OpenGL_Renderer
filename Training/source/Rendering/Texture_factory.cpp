#include "Texture_factory.h"

std::unordered_map<std::string, std::weak_ptr<Texture>> Texture_factory::texture_cache;

std::shared_ptr<Texture> Texture_factory::get(const std::string& path)
{
	if (!texture_cache[path].expired())
		return texture_cache[path].lock();

	auto texture = std::shared_ptr<Texture>(new Texture(path));
	texture_cache[path] = texture;
	return texture;
}
