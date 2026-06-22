#include "Enemy.h"

#include <cmath>

#include "Attack.h"

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
      currentPath(beginPath),
      attacks{} {
        beginPath->addEnemy(this);
      };

void Enemy::move(const int dt) {
  // verif fin de chemin
  if (!currentPath->next()) {
    return;
  }

  double targetX = currentPath->next()->getX() + 0.5;
  double targetY = currentPath->next()->getY() + 0.5;

  double moveDistance = movementSpeed * dt;
  double distanceToTarget = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));

  if (moveDistance >= distanceToTarget) {
    x = targetX;
    y = targetY;
    currentPath->removeEnemy(this);
    currentPath = currentPath->next();
    currentPath->addEnemy(this);
  }
  else {
    double ratio = moveDistance / distanceToTarget;
    x += (targetX - x) * ratio;
    y += (targetY - y) * ratio;
  }
}

Attack* Enemy::attacking(Building* targetBuilding) {
  if (currentCooldown <= 0) {
    currentCooldown = attackCooldown;
    attacks.push_back(std::make_unique<Attack>(attackDamage, attackRange, x + .5f, y + .5f,
                                               targetBuilding->getTile(), "arrow"));
    return attacks.back().get();
  }
  return nullptr;
}

void Enemy::takeDamage(int damage) {
  currentHealth -= damage;
  if (currentHealth <= 0) {
    isDead = true;
    currentPath->removeEnemy(this);
  }
}

void Enemy::kill()
{
    isDead = true;
    currentPath->removeEnemy(this);
}

void Enemy::reachObjective()
{
    kill();
    bounty = 0;
}

void Enemy::update(const context& ctx) {
  // mouvement
  move(ctx.dt);

  // animation
  animationTimer += ctx.dt;
  if (animationTimer >= timePerFrame) {
    isFrameTwo = !isFrameTwo;
    animationTimer -= timePerFrame;
  }

  // recharge de l'attaque
  if (currentCooldown > 0) {
    currentCooldown -= ctx.dt;
  }
  Building* currentTarget = (Building*)setTarget(*ctx.rand);
  // ciblage
  /*
  if (currentTarget != nullptr) {
    int distance = currentTarget->distanceTo(currentPath);
    if (distance > attackRange || !currentTarget->isAlive()) {
      currentTarget = nullptr;
    }
  }

  if (currentTarget == nullptr) {
    currentTarget = (Building*)setTarget();
  }*/

  // attaque
  if (currentTarget != nullptr && currentCooldown <= 0) {
    Attack* newAttack = attacking(currentTarget);
  }
  for (auto it = attacks.begin(); it != attacks.end();) {
    const auto& cur = (*it);
    cur->update(ctx);
    if (!cur->isActive())
      it = attacks.erase(it);
    else
      it++;
  }
}

void Enemy::drawAttacks(const context& ctx) {
  for (const auto& att : attacks) att->draw(ctx);
}

Building* Enemy::setTarget(std::mt19937& rand) {
  Building* nearest = currentPath->getNearestBuilding();
  if (!nearest) return 0;
  if (attackRange >= nearest->distanceTo(currentPath)) {
    return nearest;
  }
  return nullptr;
}

void Enemy::serialize(json& glob, json& output)
{
}

Enemy::~Enemy() = default;