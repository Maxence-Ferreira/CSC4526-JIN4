#pragma once
#include <vector>
#include "Tile.h"

class Enemy {
 protected:
  float maxHealth;
  float currentHealth;
  float movementSpeed;
  int attackDamage;
  float attackRange;
  float attackCooldown;
  double x;
  double y;
  std::unique_ptr<Tile> currentTile;



};