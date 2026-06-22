#pragma once
#include "Drawable.h"
#include "SFML/Graphics.hpp"
#include "Serializable.h"

class Entity : public Drawable, public Serializable	 {
 public:
  virtual ~Entity() = default;
  virtual bool isAlive() const = 0;
  virtual void takeDamage(int damage) = 0;
  virtual void kill() = 0;
};