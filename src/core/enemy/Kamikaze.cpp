#include "Kamikaze.h"

Kamikaze::Kamikaze(Path* beginPath) : Enemy(80.0, 0.00055, 50, 1, 0, 20, beginPath) {};

Attack* Kamikaze::attacking(Building* targetBuilding) {
    return nullptr;
    // attaque à implémenter : quand le kamikaze rejoins sa cible il explose et inflige dees degats à la cible.
}

void Kamikaze::draw(const context& ctx) {
  ctx.rm->draw({ sf::Vector2f( TILE_SIZE * (x-.5), TILE_SIZE * (y - .5)), { TILE_SIZE / 2, TILE_SIZE / 2 } }, std::string("kamikaze") + char('1' + isFrameTwo));
  this->drawAttacks(ctx);
}
