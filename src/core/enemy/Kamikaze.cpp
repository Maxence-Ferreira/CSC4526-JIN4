#include "Kamikaze.h"

#include <iostream>

Kamikaze::Kamikaze(Path* beginPath)
    : Enemy(150, 0.00055, 500, 5, 10000, 20, beginPath) {}
Kamikaze::Kamikaze(json& save, Path* p) : Enemy(save, 150, 0.00055, 500, 5, 10000, 200, p) {}

Attack* Kamikaze::attacking(Building* targetBuilding) {
  std::cout << ">>> LE KAMIKAZE A VU LA TOUR ET ACTIVE LE DETONATEUR ! <<<"
            << std::endl;
  if (!isExploding) {
    isExploding = true;
    explosionTimer = 2000.0f;
  }
  return nullptr;
}

void Kamikaze::draw(const context& ctx) {
  ctx.rm->draw({sf::Vector2f(TILE_SIZE * (x - .5), TILE_SIZE * (y - .5)),
                {TILE_SIZE / 2, TILE_SIZE / 2}},
               std::string("kamikaze") + char('1' + isFrameTwo));
  this->drawAttacks(ctx);
}

void Kamikaze::update(const context& ctx) {
  if (isExploding) {
    explosionTimer -= ctx.dt;

    if (explosionTimer <= 0) {
      Building* target = setTarget(*ctx.rand);

      if (target != nullptr) {
        target->takeDamage(attackDamage);
      }
      this->kill();
    }
    return;
  }

  Enemy::update(ctx);
}

void Kamikaze::serialize(json& glob, json& output)
{
    Enemy::serialize(glob, output);
    output["type"] = "Kamikaze";
}
