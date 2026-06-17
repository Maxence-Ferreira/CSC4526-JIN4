#pragma once
#include "Drawable.h"
#include "SFML/Graphics.hpp"

class Entity : public Drawable {
 public:
  virtual ~Entity() = default;
  virtual bool isAlive() const = 0;
  virtual void takeDamage(int damage)=0;
};