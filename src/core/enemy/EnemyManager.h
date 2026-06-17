#pragma once
#include <vector>

#include "Enemy.h"
#include "../map/Terrain.h"
#include "../Drawable.h"

class EnemyManager : public Drawable{
 private:
  std::vector<std::unique_ptr<Enemy>> enemies;
  int waveNumber;

 public:
  EnemyManager() { waveNumber = 0; };
  ~EnemyManager() = default;

  void newWave(Terrain* terrain);
  virtual void draw(const context& ctx)override;
  virtual void update(const context& ctx) override;
  void removeDeadEnemies();
  int getWaveNumber() const { return waveNumber; };
};