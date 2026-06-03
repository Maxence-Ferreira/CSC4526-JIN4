#pragma once

class Tile
{
public:
	Tile(int x, int y);
	int getX()const;
	int getY()const;
	virtual~Tile() = default;
private:
protected:
	int m_x, m_y;
};