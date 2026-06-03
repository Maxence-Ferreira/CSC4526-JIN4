#include "MeleeSoldier.h"

MeleeSoldier::MeleeSoldier(double x, double y) : Enemy(100.0, 1.0, 20, 1.0, 1.0, x, y, 10) {};

void MeleeSoldier::attack() {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}