#pragma once
#include <vector>

#include "Enemy.h"

class EnemyManager {
 private:
  std::vector<std::unique_ptr<Enemy>> enemies;
  int waveNumber;

 public:
  EnemyManager() { waveNumber = 0; };
  ~EnemyManager() = default;

  void newWave(Terrain* terrain);
  void drawEnemies();
  void updateEnemies(int dt);
  void removeDeadEnemies(Enemy* targetEnemy);
  int getWaveNumber() const { return waveNumber; };
};