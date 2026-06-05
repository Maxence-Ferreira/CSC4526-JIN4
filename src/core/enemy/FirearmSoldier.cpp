#include "FirearmSoldier.h"

FirearmSoldier::FirearmSoldier(Path* beginPath) : Enemy(100.0, 1.0, 20, 5.0, 2.0, 10, beginPath) {};

void FirearmSoldier::attacking(Tile* targetTile) {
    if (currentCooldown <= 0) {
        Attack atk(attackDamage, attackCooldown, attackRange, x, y, targetTile); // targetTile à définir
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}