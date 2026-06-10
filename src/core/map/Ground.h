#pragma once
#include "Tile.h"
#include <memory>
#include "building/Building.h"

class Building;

class Ground : public Tile {
public:
	Ground(int x, int y);
	virtual void draw(const context& ctx) override;
	void setBuilding(std::unique_ptr<Building>b);
private:
	static std::unique_ptr<sf::RectangleShape> createSprite();
	static std::unique_ptr<sf::RectangleShape> g_sprite;
	sf::Angle angle;
	std::unique_ptr<Building> m_building;
protected:
};