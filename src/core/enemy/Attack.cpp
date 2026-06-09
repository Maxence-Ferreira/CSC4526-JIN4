#include "Attack.h"

Attack::Attack(double damage, double range, double x, double y,
               Tile* targetTile)
    : damage(damage), range(range), x(x), y(y), targetTile(targetTile) {};
