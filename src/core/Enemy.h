#pragma once
#include <vector>

#include "Tile.h"

class Enemy {
 protected:
  double maxHealth;
  double currentHealth;
  double movementSpeed;
  int attackDamage;
  double attackRange;
  double attackCooldown;
  double x;
  double y;
  std::unique_ptr<Tile> currentTile;
  bool isDead;
  int bounty;              // pièces gagnées à la mort de l'ennemi
                           // visuel a mettre texture ?
  double currentCooldown;  // temps restant avant de pouvoir attaquer à nouveau

 public:
  Enemy(double maxHealth, double movementSpeed, int attackDamage,
        double attackRange, double attackCooldown, double x, double y,
        int bounty);
  virtual ~Enemy() = default;

  void move(std::vector<Tile*> path);
  virtual void attack() = 0;
  void takeDamage(double damage);
  bool isAlive() const { return !isDead; };
  int getBounty() const { return bounty; };
  double getX() const { return x; };
  double getY() const { return y; };
};