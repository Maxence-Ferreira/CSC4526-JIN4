#include "FirearmSoldier.h"

FirearmSoldier::FirearmSoldier(Path* beginPath) : Enemy(100.0, 0.0005, 20, 5.0, 2000.0, 10, beginPath) {};


void FirearmSoldier::draw(const context& ctx) {
  ctx.rm->draw({ sf::Vector2f(TILE_SIZE * (x - .5), TILE_SIZE * (y - .5)), { TILE_SIZE / 2, TILE_SIZE / 2 } }, std::string("firearm") + char('1' + isFrameTwo));
  this->drawAttacks(ctx);
}

