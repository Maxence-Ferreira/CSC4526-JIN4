#pragma once
#include "Drawable.h"
#include "common.h"
#include "Entity.h"

class Tile : public Drawable
{
public:
	Tile(int x, int y);
	int getX()const;
	int getY()const;
	Entity* getEntity() const;
	void setEntity(Entity* e);
	virtual~Tile() = default;
public:
	/// <summary>
	/// effectue la logique de dessin du tile
	/// </summary>
	/// <param name="dt">temps �coul� depuis le dernier affichage (pour g�rer les animations si besoin)</param>
	virtual void draw(const context& ctx) = 0;
protected:
	int m_x, m_y;
	Entity* entity = nullptr;
};