#pragma once 
#include "Building.h"
#include "SFML/Graphics.hpp"

class Archer : public Building {
public:
	Archer(Ground* g,int price);
	// Hérité via Building
	virtual void draw(const context& ctx) override;
	virtual void update(const context& ctx) override;
private:
	static sf::RectangleShape g_sprite;
};