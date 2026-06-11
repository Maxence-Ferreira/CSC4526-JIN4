#include "ResourceManager.h"

ResourceManager::ResourceManager(std::string tileset, std::unordered_map<std::string, sf::IntRect>config) : m_full_tileset(tileset), m_giga_buffer(sf::PrimitiveType::Triangles), m_coord(config)
{
	
}

void ResourceManager::setTileCoordinate(std::string alias, const sf::IntRect& rc)
{
	m_coord[alias] = rc;
}
