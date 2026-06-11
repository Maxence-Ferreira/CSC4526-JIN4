#pragma once
#include <vector>

#include "../Drawable.h"
#include "../map/Path.h"
#include "../map/Tile.h"
#include "Attack.h"
#include "../building/Building.h"

class Path;
class Building;
class Attack;

class Enemy : public Drawable {
 protected:
  double maxHealth;
  double currentHealth;
  double movementSpeed;  // Tile/ms
  int attackDamage;
  double attackRange;
  double attackCooldown;
  double x;
  double y;
  Path* currentPath;
  bool isDead;
  int bounty;              // pièces gagnées à la mort de l'ennemi
  double currentCooldown;  // temps restant avant de pouvoir attaquer à nouveau
  bool isFrameTwo = false;
  float animationTimer = 0.f;
  float timePerFrame = 250.0f; //4fps
  Building* currentTarget = nullptr;
  std::vector<std::unique_ptr<Attack>> attacks;

 public:
  Enemy(double maxHealth, double movementSpeed, int attackDamage,
        double attackRange, double attackCooldown, int bounty, Path* beginPath);
  virtual ~Enemy();

  void move(const int dt);
  virtual Attack* attacking(Building* targetBuilding);
  void takeDamage(int damage);
  bool isAlive() const { return !isDead; };
  int getBounty() const { return bounty; };
  double getX() const { return x; };
  double getY() const { return y; };
  virtual void update(const context& ctx) override;
  void drawAttacks(const context& ctx);
  Building* setTarget();
};