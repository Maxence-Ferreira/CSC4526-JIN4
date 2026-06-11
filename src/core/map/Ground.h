#pragma once
#include "Tile.h"
#include <memory>
#include "building/Building.h"

class Building;

class Ground : public Tile {
public:
	Ground(int x, int y);
	virtual void draw(const context& ctx) override;
	void setBuilding(Building*b);
	virtual std::vector<Entity*> getEntity() const override;
private:
	static std::unique_ptr<sf::RectangleShape> createSprite();
	static std::unique_ptr<sf::RectangleShape> g_sprite;
	sf::Angle angle;
	Building* m_building;
protected:
};