#pragma once
#include "Drawable.h"
#include "SFML/Graphics.hpp"

class Entity : public Drawable {
 public:
  virtual ~Entity() = default;
  virtual void draw(const context& ctx) = 0;
  virtual void update(const context& ctx) {};
  virtual bool isAlive() const {return false;};
  virtual void takeDamage(int damage) {};

};