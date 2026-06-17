#include "Ground.h"
#include "SFML/Graphics.hpp"
#include "common.h"
#include <random>

Ground::Ground(int x, int y):Tile(x,y), m_tex((rand() % 10) ? "ground" : "groundflower"), m_building(nullptr)
{
	m_tex += '1' + rand() % 4;
}

void Ground::draw(const context& ctx)
{
	/*
	sf::Transform t;
	t.translate({ TILE_SIZE * (m_x+.5f), TILE_SIZE * (m_y+.5f) }).rotate(angle);
	ctx.window->draw(*g_sprite,t);
	*/
	ctx.rm->draw({ {TILE_SIZE * (m_x), TILE_SIZE * (m_y)},{TILE_SIZE, TILE_SIZE } }, m_tex);
	//if(m_building)m_building->draw(ctx);
}

void Ground::setBuilding(Building* b)
{
	m_building = b;
}

std::vector<Entity*> Ground::getEntity() const
{
	return {m_building};
}

bool Ground::hasEntity() const{
	if (m_building==nullptr){return false;}
	else {return true;}
}
