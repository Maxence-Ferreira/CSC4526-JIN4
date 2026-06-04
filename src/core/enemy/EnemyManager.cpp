#include "EnemyManager.h"

#include <random>

#include "Cyrano.h"
#include "Dog.h"
#include "FirearmSoldier.h"
#include "HorseSoldier.h"
#include "Kamikaze.h"
#include "MeleeSoldier.h"
#include "Terrain.h"

void EnemyManager::newWave(Terrain* terrain) {
  waveNumber++;
  int totalEnemies = waveNumber * 5;
  std::vector<BeginPath*> entryPath = terrain->getEntry();

  enemies.push_back(std::make_unique<Cyrano>(getRandomPath(entryPath)));

  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> hundredRoll(1, 100);
  std::uniform_int_distribution<> enemyTypeRoll(0, 1);  //

  int eliteProba = std::min(
      30, (waveNumber - 1) * 3);  // elites commencent à 0% et augmentent de 3% par vague (plafond à 30%)
  int mediumProba = std::min(
      40, (waveNumber - 1) * 5);  // elites commencent à 0% et augmentent de 5% par vague (plafond à 40%)
  int baseProba =
      100 - eliteProba - mediumProba;  // le reste des ennemis sont des basiques

  for (int i = 0; i < totalEnemies - 1; i++) {
    int roll = hundredRoll(gen);
    if (roll <= eliteProba) {
      enemies.push_back(std::make_unique<Kamikaze>(getRandomPath(entryPath)));
    } else if (roll <= eliteProba + mediumProba) {
      if (enemyTypeRoll(gen) == 0) {
        enemies.push_back(
            std::make_unique<HorseSoldier>(getRandomPath(entryPath)));
      } else {
        enemies.push_back(std::make_unique<Dog>(getRandomPath(entryPath)));
      }
    } else {
      if (enemyTypeRoll(gen) == 0) {
        enemies.push_back(
            std::make_unique<FirearmSoldier>(getRandomPath(entryPath)));
      } else {
        enemies.push_back(
            std::make_unique<MeleeSoldier>(getRandomPath(entryPath)));
      }
    }
  }
}

static BeginPath* getRandomPath(const std::vector<BeginPath*>& path) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, path.size() - 1);
  return path[dis(gen)];
}

void EnemyManager::removeDeadEnemies(Enemy* targetEnemy) {
    if (targetEnemy->isAlive()) {
        return;
    }
    
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if (it->get() == targetEnemy) {
            enemies.erase(it);
            return;
        }
    }
}