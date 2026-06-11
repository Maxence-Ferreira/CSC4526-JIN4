#pragma once
#include "../map/Tile.h"
#include "../building/Building.h"
#include "../Drawable.h"

class Attack : public Drawable {
 private:
  int damage;
  double speed = 0.001; // tile/ms
  double range;
  double x;
  double y;
  Tile* targetTile;
  bool active = true;
  std::string color;

 public:
  Attack(int damage, double range, double x, double y, Tile* targetTile, std::string color);
  virtual ~Attack();
  void update(const context& ctx);
  void draw(const context& ctx);

  bool isActive() const { return active; };
};