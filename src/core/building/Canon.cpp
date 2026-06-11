#include "Canon.h"

Canon::Canon(Ground* g, int price) : Building(g, 1000, 5, 1000, 1000, price) {}

void Canon::draw(const context& ctx) {
	ctx.rm->draw({ { TILE_SIZE * getX(), TILE_SIZE * getY()},{ TILE_SIZE, TILE_SIZE} }, "canon");
	this->drawAttacks(ctx);
}

void Canon::update(const context& ctx) { Building::update(ctx); }
