#include "MeleeSoldier.h"

MeleeSoldier::MeleeSoldier(Path* beginPath) : Enemy(100.0, 1.0, 20, 1.0, 1.0, 10, beginPath) {};

void MeleeSoldier::attacking(Tile* targetTile) {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}