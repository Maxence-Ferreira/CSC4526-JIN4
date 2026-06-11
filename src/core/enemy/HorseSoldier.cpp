#include "HorseSoldier.h"

HorseSoldier::HorseSoldier(Path* beginPath) : Enemy(150.0, 0.001, 20, 5.0, 2000, 30, beginPath) {};

void HorseSoldier::draw(const context& ctx) {
	ctx.rm->draw({ sf::Vector2f(TILE_SIZE * (x - .5), TILE_SIZE * (y - .5)), { TILE_SIZE / 2, TILE_SIZE / 2 } }, std::string("horse") + char('1' + isFrameTwo));
	this->drawAttacks(ctx);
}
