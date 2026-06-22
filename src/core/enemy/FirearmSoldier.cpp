#include "FirearmSoldier.h"

FirearmSoldier::FirearmSoldier(Path* beginPath) : Enemy(100.0, 0.0005, 50, 5.0, 2000.0, 10, beginPath) {}
FirearmSoldier::FirearmSoldier(json& save, Path* current) : Enemy(save,100.0, 0.0005, 50, 5.0, 2000.0, 50, current)
{
}
;


void FirearmSoldier::draw(const context& ctx) {
  ctx.rm->draw({ sf::Vector2f(TILE_SIZE * (x - .5), TILE_SIZE * (y - .5)), { TILE_SIZE / 2, TILE_SIZE / 2 } }, std::string("firearm") + char('1' + isFrameTwo));
  this->drawAttacks(ctx);
}

void FirearmSoldier::serialize(json& glob, json& output)
{
	Enemy::serialize(glob, output);
    output["type"] = "FirearmSoldier";
}

