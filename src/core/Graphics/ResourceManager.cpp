#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager(std::string tileset, std::unordered_map<std::string, sf::IntRect>config) : 
    m_full_tileset(tileset), m_giga_buffer(sf::PrimitiveType::Triangles), m_coord(config)
{
	//
}

void ResourceManager::setTileCoordinate(std::string alias, const sf::IntRect& rc)
{
	m_coord[alias] = rc;
}

void ResourceManager::draw(const sf::FloatRect& pos, const std::string& texture)
{
    sf::IntRect texuv = m_coord[texture];
    auto megatex = m_full_tileset.getSize();
    float uvleft = texuv.position.x;
    float uvright = texuv.position.x+ texuv.size.x;
    float uvtop = texuv.position.y;
    float uvbottom = texuv.position.y + texuv.size.y;
    m_giga_buffer.append({ .position = {pos.position.x,                  pos.position.y},                .color = sf::Color::White, .texCoords = {uvleft,   uvtop} });
    m_giga_buffer.append({ .position = {pos.position.x + pos.size.x,     pos.position.y},                .color = sf::Color::White, .texCoords = {uvright,  uvtop} });
    m_giga_buffer.append({ .position = {pos.position.x + pos.size.x,     pos.position.y + pos.size.y},   .color = sf::Color::White, .texCoords = {uvright,  uvbottom} });
    m_giga_buffer.append({ .position = {pos.position.x,                  pos.position.y},                .color = sf::Color::White, .texCoords = {uvleft,   uvtop} });
    m_giga_buffer.append({ .position = {pos.position.x + pos.size.x,     pos.position.y + pos.size.y},   .color = sf::Color::White, .texCoords = {uvright,  uvbottom} });
    m_giga_buffer.append({ .position = {pos.position.x,                  pos.position.y + pos.size.y},   .color = sf::Color::White, .texCoords = {uvleft,   uvbottom} });
}

void ResourceManager::render(sf::RenderTarget* tgt, const sf::Vector2f& origin)
{
    sf::RenderStates states;
    states.texture = &m_full_tileset;
    states.transform.translate(-origin);

    tgt->draw(m_giga_buffer, states);
    m_giga_buffer.clear();

}
