#include "Ground.h"
#include "SFML/Graphics.hpp"
#include "common.h"

Ground::Ground(int x, int y):Tile(x,y)
{
}

void Ground::draw(const context& ctx)
{
	sf::RectangleShape sp({ TILE_SIZE,TILE_SIZE });
	sp.setPosition({ m_x * TILE_SIZE ,m_y * TILE_SIZE });
	sp.setFillColor(sf::Color::Green);
	sp.setOutlineColor(sf::Color(0, 200, 0));
	sp.setOutlineThickness(2);
	ctx.window->draw(sp);
}
