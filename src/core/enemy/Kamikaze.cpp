#include "Kamikaze.h"

Kamikaze::Kamikaze(Path* beginPath) : Enemy(80.0, 0.00055, 50, 1, 0, 20, beginPath) {};

Attack* Kamikaze::attacking(Building* targetBuilding) {
    return nullptr;
    // attaque à implémenter : quand le kamikaze rejoins sa cible il explose et inflige dees degats à la cible.
}

void Kamikaze::draw(const context& ctx) {
  static sf::Texture t("resources/Kamikaze_Sprite.png");
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
  this->drawAttacks(ctx);
}
