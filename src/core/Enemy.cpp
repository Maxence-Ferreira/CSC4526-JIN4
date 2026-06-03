#include "Enemy.h"
using namespace std;

Enemy::Enemy(double maxHealth, double movementSpeed, int attackDamage, double attackRange,
               double attackCooldown, double x, double y, int bounty)
    : maxHealth(maxHealth), currentHealth(maxHealth), movementSpeed(movementSpeed),
      attackDamage(attackDamage), attackRange(attackRange), attackCooldown(attackCooldown),
      x(x), y(y), isDead(false), bounty(bounty) {};

void Enemy::move(vector<Tile*> path) {}; //à faire

void Enemy::takeDamage(double damage) {
    currentHealth -= damage;
    if (currentHealth <= 0) {
        isDead = true;
    }
}


