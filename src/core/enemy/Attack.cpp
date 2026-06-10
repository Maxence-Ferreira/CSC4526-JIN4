#include "Attack.h"

#include <SFML/Graphics.hpp>
#include <cmath>

Attack::Attack(int damage, double range, double x, double y,
               Building* targetBuilding)
    : damage(damage), range(range), x(x), y(y), targetBuilding(targetBuilding) {
      };

void Attack::update(const context& ctx) {
  // projectile a atteint sa cible
  if (!active || targetBuilding == nullptr || !targetBuilding->isAlive()) {
    active = false;
    return;
  }

  double targetX = targetBuilding->getX() + 0.5;
  double targetY = targetBuilding->getY() + 0.5;

  double moveDistance = speed * ctx.dt;
  double distanceToTarget = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));

  // impact
  if (moveDistance >= distanceToTarget) {
    x = targetX;
    y = targetY;
    targetBuilding->takeDamage(damage);
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
  return;
}