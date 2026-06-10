#include "FirearmSoldier.h"

FirearmSoldier::FirearmSoldier(Path* beginPath) : Enemy(100.0, 1.0, 20, 5.0, 2.0, 10, beginPath) {};


void FirearmSoldier::draw(const context& ctx) {
  static sf::Texture t("resources/FirearmSoldier_Sprite.png");
  sf::Sprite sp(t);

  int frameX =
      isFrameTwo
          ? 16
          : 0;  // si isFrameTwo est vrai, on utilise la deuxième frame (16
                // pixels de décalage), sinon la première (0 pixels de décalage)
  sp.setTextureRect(sf::IntRect({frameX, 0}, {16, 16}));
  sp.setOrigin({ TEX_IN_TILE, TEX_IN_TILE });
  sp.setPosition({(float)(this->x * TILE_SIZE), (float)(this->y * TILE_SIZE)});
  ctx.window->draw(sp);
  this->drawAttacks(ctx);
}

void FirearmSoldier::resetCooldown(){
    attackCooldown = 2.0;
}