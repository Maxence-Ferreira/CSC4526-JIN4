#include "Cyrano.h"

Cyrano::Cyrano(Path* beginPath) : Enemy(500.0, 1.0, 30, 3.0, 1.0, 100, beginPath) {};

void Cyrano::attacking(Tile* targetTile) {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}