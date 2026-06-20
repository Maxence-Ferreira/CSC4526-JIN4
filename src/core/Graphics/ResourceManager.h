#pragma once

#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"

class ResourceManager
{
public:
	ResourceManager(std::string tileset = "resources/tileset.png", std::unordered_map<std::string, sf::IntRect>config = {});
	void setTileCoordinate(std::string alias, const sf::IntRect& rc);
	void draw(const sf::FloatRect& morpho, const std::string& texture, const sf::Color& filter=sf::Color::White);
	void render(sf::RenderTarget* tgt, const sf::Vector2f& origin = {});
protected:
private:
	std::unordered_map<std::string, sf::IntRect>m_coord;
	sf::VertexArray m_giga_buffer;
	sf::Texture m_full_tileset;
};