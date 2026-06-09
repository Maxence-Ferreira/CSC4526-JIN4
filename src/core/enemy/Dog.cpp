#include "Dog.h"

Dog::Dog(Path* beginPath) : Enemy(75.0, 3.0, 20, 1.0, 0.5, 15, beginPath) {};

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
  sp.setPosition({(float)(this->x * TILE_SIZE), (float)(this->y * TILE_SIZE)});
  ctx.window->draw(sp);
}