#include "Archer.h"

#include "SFML/Graphics.hpp"

Archer::Archer(Ground* g, int price)
    : Building(g, 1000, 40, 1, 1000, price) {}

void Archer::draw(const context& ctx) {
  ctx.rm->draw({ { TILE_SIZE * getX(), TILE_SIZE * getY()},{ TILE_SIZE, TILE_SIZE} }, "archer");
  this->drawAttacks(ctx);
}

void Archer::update(const context& ctx) { Building::update(ctx); }

Tile* Archer::setTarget(std::mt19937& rand)
{
    std::vector<Path*> nonempty = {};
    for (Path* p : m_tracked_path)if (p->hasEntity())nonempty.push_back(p);
    if (nonempty.empty())return nullptr;
    std::uniform_int_distribution<> path_i(0, nonempty.size()-1);
    Path* choosen = nonempty[path_i(rand)];
    return choosen;
}
