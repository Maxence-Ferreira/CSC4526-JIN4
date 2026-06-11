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
  void draw(const context& ctx);
  void updateEnemies(const context& ctx);
  void removeDeadEnemies(Enemy* targetEnemy);
  int getWaveNumber() const { return waveNumber; };
};