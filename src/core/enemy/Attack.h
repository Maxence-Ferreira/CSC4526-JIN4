#pragma once
#include "../map/Tile.h"
#include "../building/Building.h"
#include "../Drawable.h"

class Attack : public Drawable {
 private:
  int damage;
  double speed = 0.005; // tile/ms
  double range;
  double x;
  double y;
  Building* targetBuilding;
  bool active = true;

 public:
  Attack(int damage, double range, double x, double y, Building* targetBuilding);
  virtual ~Attack() = default;
  void update(const context& ctx);
  void draw(const context& ctx);

  bool isActive() const { return active; };
};