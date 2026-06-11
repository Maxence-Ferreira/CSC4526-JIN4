#include "Archer.h"

#include "SFML/Graphics.hpp"

Archer::Archer(Ground* g, int price)
    : Building(g, 1000, 5, 1000, 1000, price) {}

void Archer::draw(const context& ctx) {
  sf::Transform t;
  t.translate(
      sf::Vector2f(TILE_SIZE * (getX() + .5), TILE_SIZE * (getY() + .5)));
  ctx.window->draw(g_sprite, t);
  this->drawAttacks(ctx);
}

void Archer::update(const context& ctx) { Building::update(ctx); }

static sf::RectangleShape create() {
  sf::RectangleShape r({TILE_SIZE, TILE_SIZE});
  static sf::Texture tex("resources/ArcherTower.png");
  r.setOrigin({TILE_SIZE / 2, TILE_SIZE / 2});
  r.setTexture(&tex);
  return r;
}
sf::RectangleShape Archer::g_sprite = create();