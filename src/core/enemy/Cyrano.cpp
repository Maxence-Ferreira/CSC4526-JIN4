#include "Cyrano.h"

#include "SFML/Graphics.hpp"
#include "common.h"

Cyrano::Cyrano(Path* beginPath)
    : Enemy(500.0, 1.0, 30, 3.0, 1.0, 100, beginPath) {};

void Cyrano::attacking(Tile* targetTile) {
  if (currentCooldown <= 0) {
    // attaque à implémenter
    currentCooldown = attackCooldown;
  }
}

void Cyrano::draw(const context& ctx) {
  static sf::Texture t("../../../resources/SpriteSheets/Cyrano_Sprite.png");
  sf::Sprite sp(t);
  sp.setTexture(t);

  int frameX =
      isFrameTwo
          ? 16
          : 0;  // si isFrameTwo est vrai, on utilise la deuxième frame (16
                // pixels de décalage), sinon la première (0 pixels de décalage)
  sp.setTextureRect(sf::IntRect({frameX, 0}, {16, 16}));
  sp.setOrigin({8.0f, 8.0f});
  sp.setScale({2.0f, 2.0f});
  sp.setPosition({(float)(this->x * TILE_SIZE), (float)(this->y * TILE_SIZE)});
  ctx.window->draw(sp);
}
