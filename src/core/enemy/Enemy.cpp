#include "Enemy.h"

#include <cmath>

Enemy::Enemy(double maxHealth, double movementSpeed, int attackDamage,
             double attackRange, double attackCooldown,
             int bounty, Path* beginPath)
    : maxHealth(maxHealth),
      currentHealth(maxHealth),
      movementSpeed(movementSpeed),
      attackDamage(attackDamage),
      attackRange(attackRange),
      attackCooldown(attackCooldown),
      x(beginPath->getX() + 0.5),
      y(beginPath->getY() + 0.5),
      isDead(false),
      bounty(bounty),
      currentCooldown(0),
      currentPath(beginPath) {};

void Enemy::move(const int dt) {
  double targetX = currentPath->next()->getX() + 0.5;
  double targetY = currentPath->next()->getY() + 0.5;

  double moveDistance = movementSpeed * dt;
  double distanceToTarget = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));

  double ratio = moveDistance / distanceToTarget;
  x += (targetX - x) * ratio;
  y += (targetY - y) * ratio;

  if ((int)x == targetX && (int)y == targetY) {
    currentPath = currentPath->next();
  };
}

  void Enemy::takeDamage(double damage) {
    currentHealth -= damage;
    if (currentHealth <= 0) {
      isDead = true;
    }
  }
