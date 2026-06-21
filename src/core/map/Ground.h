#pragma once
#include "Tile.h"
#include <memory>
#include "building/Building.h"
#include "Path.h"

class Building;

class Ground : public Tile {
public:
	Ground(int x, int y);
	virtual void draw(const context& ctx) override;
	void setBuilding(Building*b);
	virtual std::vector<Entity*> getEntity() const override;
	virtual bool hasEntity() const override;
private:
	std::string m_tex;
	Building* m_building;
	virtual void serialize(json& output)override;
protected:
};