#pragma once 
#include "Building.h"
#include "SFML/Graphics.hpp"

class Archer : public Building {
public:
	Archer(int price);
	Archer(const Archer& a);
	// H�rit� via Building
	virtual void draw(const context& ctx) override;
	virtual void update(const context& ctx) override;
	virtual Tile* setTarget(std::mt19937& rand) override;
	virtual std::string projectileSkin()const override;
	virtual std::unique_ptr<Building> clone(Ground* ground) override;
private:

	// Hérité via Building
	virtual std::unique_ptr<Building> clone() override;
};