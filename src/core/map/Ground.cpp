#include "Ground.h"
#include "SFML/Graphics.hpp"
#include "common.h"
#include <random>

Ground::Ground(int x, int y):Tile(x,y),angle(sf::degrees((rand()%4)*90))
{
}

void Ground::draw(const context& ctx)
{
	sf::Transform t;
	t.translate({ TILE_SIZE * m_x, TILE_SIZE * m_y }).rotate(angle);
	ctx.window->draw(*g_sprite,t);
}

std::unique_ptr<sf::RectangleShape> Ground::g_sprite = Ground::createSprite();
std::unique_ptr<sf::RectangleShape> Ground::createSprite()
{
	static sf::Texture t("resources/ground.png");
	sf::RectangleShape sp({ TILE_SIZE,TILE_SIZE });
	sp.setPosition({ -TILE_SIZE / 2, -TILE_SIZE / 2 });
	sp.setTexture(&t);
	return std::make_unique<sf::RectangleShape>(sp);
}
