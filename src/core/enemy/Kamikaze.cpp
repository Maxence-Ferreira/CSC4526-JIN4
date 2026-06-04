#include "Kamikaze.h"

Kamikaze::Kamikaze(double x, double y) : Enemy(80.0, 1.5, 50, 1, 0, x, y, 20,0) {};

void Kamikaze::attacking(Tile* targetTile) {
    // attaque à implémenter : quand le kamikaze rejoins sa cible il explose et inflige dees degats à la cible.
}