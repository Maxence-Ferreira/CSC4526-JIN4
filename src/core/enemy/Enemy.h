#pragma once
#include <vector>

#include "../map/Tile.h"
#include "../map/Path.h"
#include "Attack.h"

class Enemy {
 protected:
  double maxHealth;
  double currentHealth;
  double movementSpeed; //Tile/ms
  int attackDamage;
  double attackRange;
  double attackCooldown;
  double x;
  double y;
  Path* currentPath; 
  bool isDead;
  int bounty;              // pièces gagnées à la mort de l'ennemi
  // visuel a mettre texture ?
  double currentCooldown;  // temps restant avant de pouvoir attaquer à nouveau

 public:
  Enemy(double maxHealth, double movementSpeed, int attackDamage,
        double attackRange, double attackCooldown, double x, double y,
        int bounty, Path* beginPath);
  virtual ~Enemy() = default;

  void move(const int dt);
  virtual void attack() = 0;
  void takeDamage(double damage);
  bool isAlive() const { return !isDead; };
  int getBounty() const { return bounty; };
  double getX() const { return x; };
  double getY() const { return y; };
};