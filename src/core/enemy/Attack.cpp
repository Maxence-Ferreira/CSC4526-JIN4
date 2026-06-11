#include "Attack.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Enemy.h"

Attack::Attack(int damage, double range, double x, double y,
               Tile* targetTile)
    : damage(damage), range(range), x(x), y(y), targetTile(targetTile) {
      };

void Attack::update(const context& ctx) {
  Entity* target = targetTile->getEntity();
  // projectile a atteint sa cible
  if (!active || target == nullptr || !target->isAlive()) {
    active = false;
    return;
  }

  double targetX = targetTile->getX() + 0.5;
  double targetY = targetTile->getY() + 0.5;

  double moveDistance = speed * ctx.dt;
  double distanceToTarget = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));

  // impact
  if (moveDistance >= distanceToTarget) {
    x = targetX;
    y = targetY;
    target->takeDamage(damage);
    active = false;
  }

  // deplacement du projectile
  else {
    double ratio = moveDistance / distanceToTarget;
    x += (targetX - x) * ratio;
    y += (targetY - y) * ratio;
  }
}

void Attack::draw(const context& ctx) {
  if (!isActive()) {return;}

  //création d'une balle
  sf::CircleShape projectile(0.15f*TILE_SIZE);
  projectile.setFillColor(sf::Color::Red);
  projectile.setOrigin({projectile.getRadius(), projectile.getRadius()});
  projectile.setPosition({(float)(x*TILE_SIZE), (float)(y*TILE_SIZE)});

  ctx.window->draw(projectile);
}

Attack::~Attack() = default;