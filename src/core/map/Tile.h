#pragma once
#include "Drawable.h"
#include "common.h"
class Tile : public Drawable
{
public:
	Tile(int x, int y);
	int getX()const;
	int getY()const;
	virtual~Tile() = default;
public:
	/// <summary>
	/// effectue la logique de dessin du tile
	/// </summary>
	/// <param name="dt">temps écoulé depuis le dernier affichage (pour gérer les animations si besoin)</param>
	virtual void draw(const context& ctx) = 0;
protected:
	int m_x, m_y;
};