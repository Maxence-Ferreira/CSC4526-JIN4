#include "FirearmSoldier.h"

FirearmSoldier::FirearmSoldier(double x, double y) : Enemy(100.0, 1.0, 20, 5.0, 2.0, x, y, 10), currentCooldown(0) {};

void FirearmSoldier::attack() {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}