#include "Dog.h"

Dog::Dog(Path* beginPath) : Enemy(75.0, 0.0015, 20, 1.0, 500, 15, beginPath) {};

void Dog::draw(const context& ctx) {
  static sf::Texture t("resources/Dog_Sprite.png");
  sf::Sprite sp(t);

  int frameX =
      isFrameTwo
          ? 16
          : 0;  // si isFrameTwo est vrai, on utilise la deuxième frame (16
                // pixels de décalage), sinon la première (0 pixels de décalage)
  sp.setTextureRect(sf::IntRect({frameX, 0}, {16, 16}));
  sp.setOrigin({ TEX_IN_TILE, TEX_IN_TILE});
  sp.setScale({TEX_IN_TILE*0.5, TEX_IN_TILE*0.5});
  sp.setPosition({(float)(this->x * TILE_SIZE), (float)(this->y * TILE_SIZE)});
  this->drawAttacks(ctx);
}
