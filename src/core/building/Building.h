#pragma once
#include "Drawable.h"
#include "map/Ground.h"

class Building : public Drawable{
public:

	int getX() const;
	int getY() const;
	int distanceTo(Tile*) const;
protected:
private:
	Ground* m_tile;
};