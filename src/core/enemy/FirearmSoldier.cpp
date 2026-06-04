#include "FirearmSoldier.h"

FirearmSoldier::FirearmSoldier(double x, double y) : Enemy(100.0, 1.0, 20, 5.0, 2.0, x, y, 10,0) {};

void FirearmSoldier::attacking(Tile* targetTile) {
    if (currentCooldown <= 0) {
        Attack atk(attackDamage, attackCooldown, attackRange, x, y, targetTile); // targetTile à définir
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}