#include "HorseSoldier.h"

HorseSoldier::HorseSoldier(double x, double y) : Enemy(150.0, 2.0, 20, 5.0, 2, x, y, 30) {};

void HorseSoldier::attack() {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}