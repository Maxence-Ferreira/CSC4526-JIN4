#include "Cyrano.h"

Cyrano::Cyrano(double x, double y) : Enemy(500.0, 1.0, 30, 3.0, 1.0, x, y, 100, 0) {};

void Cyrano::attack() {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}