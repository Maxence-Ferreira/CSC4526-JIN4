#pragma once 
#include "Building.h"
#include "SFML/Graphics.hpp"

class Canon : public Building {
public:
	Canon(int price);
	// H�rit� via Building
	virtual void draw(const context& ctx) override;
	virtual void update(const context& ctx) override;
	virtual Tile* setTarget(std::mt19937& rand) override;
	virtual std::unique_ptr<Building> clone(Ground* ground) override;
	virtual std::unique_ptr<Building> clone() override;
private:
};