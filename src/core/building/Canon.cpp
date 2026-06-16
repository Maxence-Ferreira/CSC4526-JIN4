#include "Canon.h"

Canon::Canon(Ground* g, int price) : Building(g, 1000, 5, 3, 1000, price) {}

void Canon::draw(const context& ctx) {
	ctx.rm->draw({ { TILE_SIZE * getX(), TILE_SIZE * getY()},{ TILE_SIZE, TILE_SIZE} }, "canon");
	this->drawAttacks(ctx);
}

void Canon::update(const context& ctx) { Building::update(ctx); }

Tile* Canon::setTarget(std::mt19937& rand)
{
	//choisis le plus devant avec des ennemis dessus
	Path* cur=0;
	for (Path* it : m_tracked_path)if (it->hasEntity())
	{
		cur = it;
		break;
	}
	if(!cur)return nullptr;
	Path* ret = cur;
	while (cur->next() && m_tracked_path.contains(cur->next()))
	{
		cur = cur->next();
		if (cur->hasEntity())ret = cur;
	}
	return ret;
}
