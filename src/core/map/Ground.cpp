#include "Ground.h"
#include "SFML/Graphics.hpp"
#include "common.h"

Ground::Ground(int x, int y):Tile(x,y)
{
}

void Ground::draw(const context& ctx)
{
	static std::unique_ptr<sf::Drawable> sprite(getSprite());
	sf::Transform t;
	t.translate({ TILE_SIZE * m_x, TILE_SIZE * m_y });
	ctx.window->draw(*sprite,t);
}

std::unique_ptr<sf::Drawable> Ground::getSprite()
{
	sf::RectangleShape sp({ TILE_SIZE,TILE_SIZE });
	sf::Texture t("resources/map/ground.png");
	sp.setTexture(&t);
	return std::make_unique<sf::RectangleShape>(sp);
}
