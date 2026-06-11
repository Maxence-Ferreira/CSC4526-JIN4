#include "Archer.h"

#include "SFML/Graphics.hpp"

Archer::Archer(Ground* g, int price)
    : Building(g, 1000, 5, 1000, 1000, price) {}

void Archer::draw(const context& ctx) {
  ctx.rm->draw({ { TILE_SIZE * getX(), TILE_SIZE * getY()},{ TILE_SIZE, TILE_SIZE} }, "archer");
  this->drawAttacks(ctx);
}

void Archer::update(const context& ctx) { Building::update(ctx); }
