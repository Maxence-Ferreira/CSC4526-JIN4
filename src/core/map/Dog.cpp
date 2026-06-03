#include "Dog.h"

Dog::Dog(double x, double y) : Enemy(75.0, 3.0, 20, 1.0, 0.5, x, y, 15) {};

void Dog::attack() {
    if (currentCooldown <= 0) {
        // attaque à implémenter 
        currentCooldown = attackCooldown; 
    }
}