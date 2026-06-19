#include "Dog.h"

Dog::Dog(Path* beginPath) : Enemy(75.0, 0.0015, 100, 1.0, 500, 15, beginPath) {};

void Dog::draw(const context& ctx) {
	ctx.rm->draw({ sf::Vector2f(TILE_SIZE * (x - .5), TILE_SIZE * (y - .5)), { TILE_SIZE / 2, TILE_SIZE / 2 } }, std::string("dog") + char('1' + isFrameTwo));
  this->drawAttacks(ctx);
}
