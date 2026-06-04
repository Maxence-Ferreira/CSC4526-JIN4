#pragma once
#include "../map/Tile.h"

class Attack {
 private:
  double damage;
  double speed;
  double range;
  double x;
  double y;
  Tile* targetTile;
  // visuel a mettre texture ?

 public:
  Attack(double damage, double speed, double range, double x, double y, Tile* targetTile);
  virtual ~Attack() = default;
  
};