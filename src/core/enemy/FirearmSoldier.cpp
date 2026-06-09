#include "FirearmSoldier.h"

FirearmSoldier::FirearmSoldier(Path* beginPath) : Enemy(100.0, 1.0, 20, 5.0, 2.0, 10, beginPath) {};

void FirearmSoldier::attacking(Tile* targetTile) {
    if (currentCooldown <= 0) {
        Attack atk(attackDamage, attackCooldown, attackRange, x, y, targetTile); // targetTile à définir
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}

void FirearmSoldier::draw(const context& ctx) {
  static sf::Texture t("../../../resources/SpriteSheets/FirearmSoldier_Sprite.png");
  sf::Sprite sp(t);
  sp.setTexture(t);

  int frameX =
      isFrameTwo
          ? 16
          : 0;  // si isFrameTwo est vrai, on utilise la deuxième frame (16
                // pixels de décalage), sinon la première (0 pixels de décalage)
  sp.setTextureRect(sf::IntRect({frameX, 0}, {16, 16}));
  sp.setOrigin({8.0f, 8.0f});
  sp.setPosition({(float)(this->x * TILE_SIZE), (float)(this->y * TILE_SIZE)});
  ctx.window->draw(sp);
}