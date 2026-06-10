#include "Enemy.h"

#include <cmath>

Enemy::Enemy(double maxHealth, double movementSpeed, int attackDamage,
             double attackRange, double attackCooldown, int bounty,
             Path* beginPath)
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

Attack* Enemy::attacking(Building* targetBuilding)
{
    if (currentCooldown <= 0) {
        currentCooldown = attackCooldown;
        return new Attack(attackDamage, attackRange, x, y, targetBuilding);
    }
    return nullptr;

}

void Enemy::takeDamage(int damage) {
  currentHealth -= damage;
  if (currentHealth <= 0) {
    isDead = true;
  }
}

void Enemy::update(const context& ctx) {
  //mouvement
  // this->move(ctx.dt);

  //animation
  animationTimer += ctx.dt;
  if (animationTimer >= timePerFrame) {
    isFrameTwo = !isFrameTwo;
    animationTimer -= timePerFrame;
  }

  //recharge de l'attaque
  if (currentCooldown > 0) {
    currentCooldown -= ctx.dt;
  }

  return;
  //ciblage
  if (currentTarget != nullptr) {
    int distance = currentTarget->distanceTo(currentPath);
    if (distance>attackRange){
      currentTarget = nullptr;
    }
    if(!currentTarget->isAlive()){
      currentTarget = nullptr;
    }
  }

  if (currentTarget == nullptr) {
    currentTarget = setTarget();
  }

  //attaque
  if (currentTarget != nullptr && currentCooldown <= 0) {
      Attack* newAttack = attacking(currentTarget);
      //
  }
}

Building* Enemy::setTarget() {
    Building* nearest = currentPath->getNearestBuilding();
    if (attackRange >=
        nearest->distanceTo(currentPath)) {
        return nearest;
    }
    return nullptr;
}
