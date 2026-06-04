#include "Dog.h"

Dog::Dog(Path* beginPath) : Enemy(75.0, 3.0, 20, 1.0, 0.5, 15, beginPath) {};

void Dog::attacking(Tile* targetTile) {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}