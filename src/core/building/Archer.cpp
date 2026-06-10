#include "Archer.h"

Archer::Archer(Ground* g, int price):Building(g,1000,5,0,10, price)
{
}

void Archer::draw(const context& ctx)
{
	sf::Transform t;
	t.translate(sf::Vector2f( TILE_SIZE * (getX() + .5),TILE_SIZE * (getY() + .5) ));
	ctx.window->draw(g_sprite, t);
}

void Archer::update(const context& ctx)
{
}
static sf::RectangleShape create()
{
	sf::RectangleShape r({ TILE_SIZE,TILE_SIZE });
	static sf::Texture tex("resources/ArcherTower.png");
	r.setOrigin({ TILE_SIZE / 2,TILE_SIZE / 2 });
	r.setTexture(&tex);
	return r;
}
sf::RectangleShape Archer::g_sprite = create();