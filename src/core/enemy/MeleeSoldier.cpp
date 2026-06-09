#include "MeleeSoldier.h"

MeleeSoldier::MeleeSoldier(Path* beginPath) : Enemy(100.0, 1.0, 20, 1.0, 1.0, 10, beginPath) {};


void MeleeSoldier::draw(const context& ctx) {
  static sf::Texture t("../../../resources/SpriteSheets/MeleeSoldier_Sprite.png");
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