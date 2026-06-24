#include "MeleeSoldier.h"

MeleeSoldier::MeleeSoldier(Path* beginPath) : Enemy(100.0, 0.0005, 50, 1.0, 1000.0, 10, beginPath) {}
MeleeSoldier::MeleeSoldier(json& save, Path* p) : Enemy(save, 100.0, 0.0005, 50, 1.0, 1000.0, 50, p)
{
}


void MeleeSoldier::draw(const context& ctx) {
    ctx.rm->draw({ sf::Vector2f(TILE_SIZE * (x - .5), TILE_SIZE * (y - .5)),
                  {TILE_SIZE / 2, TILE_SIZE / 2} },
        std::string("melee") + char('1' + isFrameTwo));
    this->drawAttacks(ctx);

}

void MeleeSoldier::serialize(json& glob, json& output)
{
    Enemy::serialize(glob, output);
    output["type"] = "MeleeSoldier";
}

