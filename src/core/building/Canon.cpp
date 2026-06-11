#include "Canon.h"

Canon::Canon(Ground* g, int price):Building(g,1000,5,1000,1000, price)
{
}

void Canon::draw(const context& ctx)
{
	sf::Transform t;
	t.translate(sf::Vector2f( TILE_SIZE * (getX() + .5),TILE_SIZE * (getY() + .5) ));
	ctx.window->draw(g_sprite, t);
}

void Canon::update(const context& ctx)
{
}
static sf::RectangleShape create()
{
	sf::RectangleShape r({ TILE_SIZE,TILE_SIZE });
	static sf::Texture tex("resources/CanonTower.png");
	r.setOrigin({ TILE_SIZE / 2,TILE_SIZE / 2 });
	r.setTexture(&tex);
	return r;
}
sf::RectangleShape Canon::g_sprite = create();