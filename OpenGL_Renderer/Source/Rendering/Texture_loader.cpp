#include "Texture_loader.h"

std::unordered_map<std::string, std::weak_ptr<Texture>> Texture_loader::m_texture_cache;

std::shared_ptr<Texture> Texture_loader::load(const std::string& path)
{
	if (!m_texture_cache[path].expired())
		return m_texture_cache[path].lock();

	auto texture = std::shared_ptr<Texture>(new Texture(path));
	m_texture_cache[path] = texture;
	return texture;
}
