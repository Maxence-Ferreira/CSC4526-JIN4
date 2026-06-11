#include "MeleeSoldier.h"

MeleeSoldier::MeleeSoldier(Path* beginPath) : Enemy(100.0, 0.0005, 20, 1.0, 1000.0, 10, beginPath) {};


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
  sp.setScale({TEX_IN_TILE*0.5, TEX_IN_TILE*0.5});
  sp.setPosition({(float)(this->x * TILE_SIZE), (float)(this->y * TILE_SIZE)});
  ctx.window->draw(sp);
  ctx.rm->draw({ sf::Vector2f(TILE_SIZE * (x - .5), TILE_SIZE * (y - .5)),{TILE_SIZE/2, TILE_SIZE/2} }, std::string("melee") + char('1' + isFrameTwo));
  this->drawAttacks(ctx);
}

