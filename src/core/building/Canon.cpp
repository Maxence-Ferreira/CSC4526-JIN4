#include "Canon.h"

Canon::Canon(int price) : Building(1000, 50, 1, 1000, price) {}

void Canon::draw(const context& ctx) {
  if (m_levelUp_timer > 0.0f) {
    ctx.rm->draw({{TILE_SIZE * (getX()-.25f), TILE_SIZE * (getY()-.25f)},{TILE_SIZE * 1.5, TILE_SIZE * 1.5}},"canon");
  } else {
    ctx.rm->draw(
        {{TILE_SIZE * getX(), TILE_SIZE * getY()}, {TILE_SIZE, TILE_SIZE}}, "canon");
  }
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

std::unique_ptr<Building> Canon::clone(Ground* ground)
{
	std::unique_ptr<Canon> ptr(std::make_unique<Canon>(*this));
	ptr->setOnTile(ground);
	return std::move(ptr);
}

std::unique_ptr<Building> Canon::clone()
{
	return std::make_unique<Canon>(*this);
}

std::string Canon::projectileSkin() const
{
	return "canonball";
}

void Canon::serialize(json& glob, json& output)
{
	Building::serialize(glob,output);
	output["type"] = "Canon";
}

