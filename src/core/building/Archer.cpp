#include "Archer.h"

#include "SFML/Graphics.hpp"

Archer::Archer(int price)
    : Building(1000, 40, 1, 1000, price) {}

Archer::Archer(const Archer& a):Building(a)
{
}

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

std::unique_ptr<Building> Archer::clone(Ground* ground)
{
    std::unique_ptr<Archer> ptr(std::make_unique<Archer>(*this));
    ptr->setOnTile(ground);
    return std::move(ptr);
}

std::unique_ptr<Building> Archer::clone()
{
    return std::make_unique<Archer>(*this);
}
