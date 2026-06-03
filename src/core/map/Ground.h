#pragma once
#include "Tile.h"

class Ground : public Tile {
public:
	Ground(int x, int y);
	virtual void draw(const context& ctx) override;
private:
protected:
};