#include "MeleeSoldier.h"

MeleeSoldier::MeleeSoldier(Path* beginPath) : Enemy(100.0, 1.0, 20, 1.0, 1.0, 10, beginPath) {};


void MeleeSoldier::draw(const context& ctx) {
  static sf::Texture t("resources/MeleeSoldier_Sprite.png");
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

void MeleeSoldier::resetCooldown(){
    attackCooldown = 1.0;
}