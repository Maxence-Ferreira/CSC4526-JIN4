#include "Cyrano.h"

#include "SFML/Graphics.hpp"
#include "common.h"

Cyrano::Cyrano(Path* beginPath)
    : Enemy(500.0, 0.0005, 200, 1000.0, 1000.0, 100, beginPath) {}
Cyrano::Cyrano(json& save, Path* current) : Enemy(save, 500.0, 0.0005, 200, 1000.0, 1000.0, 100, current)
{
}
;


void Cyrano::draw(const context& ctx) {
  ctx.rm->draw({ sf::Vector2f( TILE_SIZE * (x-.5), TILE_SIZE * (y - .5)),{TILE_SIZE, TILE_SIZE}}, std::string("cyrano") + char('1' + isFrameTwo));
  this->drawAttacks(ctx);
}

void Cyrano::serialize(json& glob, json& output)
{
    Enemy::serialize(glob, output);
    output["type"] = "Cyrano";
}


