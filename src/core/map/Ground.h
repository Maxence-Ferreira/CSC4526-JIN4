#pragma once
#include "Tile.h"

class Ground : public Tile {
public:
	Ground(int x, int y);
	virtual void draw(const context& ctx) override;
private:
	static std::unique_ptr<sf::RectangleShape> createSprite();
	sf::Angle angle;
	static std::unique_ptr<sf::RectangleShape> g_sprite;
protected:
};