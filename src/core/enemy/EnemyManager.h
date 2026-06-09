#pragma once
#include <vector>

#include "Enemy.h"
#include "../map/Terrain.h"

class EnemyManager {
 private:
  std::vector<std::unique_ptr<Enemy>> enemies;
  int waveNumber;
  int money;

 public:
  EnemyManager() { waveNumber = 0; };
  ~EnemyManager() = default;

  void newWave(Terrain* terrain);
  void drawEnemies();
  void updateEnemies(int dt);
  void removeDeadEnemies(Enemy* targetEnemy);
  int getWaveNumber() const { return waveNumber; };
};