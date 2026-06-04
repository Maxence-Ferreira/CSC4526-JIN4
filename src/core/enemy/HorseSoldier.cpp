#include "HorseSoldier.h"

HorseSoldier::HorseSoldier(Path* beginPath) : Enemy(150.0, 2.0, 20, 5.0, 2, 30, beginPath) {};

void HorseSoldier::attacking(Tile* targetTile) {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}