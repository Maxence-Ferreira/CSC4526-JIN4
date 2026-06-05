#pragma once
#include "Tile.h"

class Ground : public Tile {
public:
	Ground(int x, int y);
	virtual void draw(const context& ctx) override;
private:
	virtual std::unique_ptr<sf::Drawable> getSprite() override;
	sf::Angle angle;
protected:
};