#include "EnemyManager.h"

#include <random>
#include <queue>


#include "../map/BeginPath.h"
#include "../map/Terrain.h"
#include "Cyrano.h"
#include "Dog.h"
#include "FirearmSoldier.h"
#include "HorseSoldier.h"
#include "Kamikaze.h"
#include "MeleeSoldier.h"

EnemyManager::EnemyManager(int difficulty)
    : Drawable(), m_difficulty(difficulty), waveNumber(0), m_spawnerTimer(0.f), m_terrain(nullptr) {
}

static BeginPath* getRandomPath(const std::vector<BeginPath*>& path) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, path.size() - 1);
  return path[dis(gen)];
}

// crée un ensemble d'ennemis a chaque vague
void EnemyManager::newWave(Terrain* terrain) {
  m_terrain=terrain;
  waveNumber++;
  int totalEnemies = 5 + waveNumber * m_difficulty;
  std::vector<BeginPath*> entryPath = terrain->getEntry();

  m_spawner.push(EnemyType::Cyrano);
  //enemies.push_back(std::make_unique<Cyrano>(getRandomPath(entryPath)));

  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> hundredRoll(1, 100);
  std::uniform_int_distribution<> enemyTypeRoll(0, 1);  //

  //diff = {2,3,4,5,6}
  int eliteProba = std::min(
      30*(m_difficulty/2), (waveNumber - 1) * 2*(m_difficulty-1));  // elites commencent à 0% et augmentent de 2*diff%
                                  // par vague (plafond à 30(*diff/2)%)
  int mediumProba = std::min(
      30/(m_difficulty/2), (waveNumber - 1) * 4*(m_difficulty-1));  // elites commencent à 0% et augmentent de 4*(diff-1)%
                                  // par vague (plafond à 30/(diff/2)%)
  int baseProba =
      100 - eliteProba - mediumProba;  // le reste des ennemis sont des basiques

  for (int i = 0; i < totalEnemies - 1; i++) {
    int roll = hundredRoll(gen);
    if (roll <= eliteProba) {
      m_spawner.push(EnemyType::Kamikaze);
    } else if (roll <= eliteProba + mediumProba) {
      if (enemyTypeRoll(gen) == 0) {
        m_spawner.push(EnemyType::HorseSoldier);
      } else {
        m_spawner.push(EnemyType::Dog);
      }
    } else {
      if (enemyTypeRoll(gen) == 0) {
        m_spawner.push(EnemyType::FirearmSoldier);
      } else {
        m_spawner.push(EnemyType::MeleeSoldier);
      }
    }
  }
}

void EnemyManager::spawnEnemy(EnemyType type) {
    if (!m_terrain) return;
    std::vector<BeginPath*> entryPath = m_terrain->getEntry();

    switch (type) {
        case EnemyType::Cyrano:
            enemies.push_back(std::make_unique<Cyrano>(getRandomPath(entryPath)));
            break;
        case EnemyType::Kamikaze:
            enemies.push_back(std::make_unique<Kamikaze>(getRandomPath(entryPath)));
            break;
        case EnemyType::HorseSoldier:
            enemies.push_back(std::make_unique<HorseSoldier>(getRandomPath(entryPath)));
            break;
        case EnemyType::Dog:
            enemies.push_back(std::make_unique<Dog>(getRandomPath(entryPath)));
            break;
        case EnemyType::FirearmSoldier:
            enemies.push_back(std::make_unique<FirearmSoldier>(getRandomPath(entryPath)));
            break;
        case EnemyType::MeleeSoldier:
            enemies.push_back(std::make_unique<MeleeSoldier>(getRandomPath(entryPath)));
            break;
    }
}

void EnemyManager::removeDeadEnemies() {
  std::erase_if(enemies,
                [](std::unique_ptr<Enemy>& u) { return !u->isAlive(); });
}

void EnemyManager::update(const context& ctx) {
  if(!m_spawner.empty()){
    m_spawnerTimer -= ctx.dt;
    if(m_spawnerTimer <=0){
      spawnEnemy(m_spawner.front());
      m_spawner.pop();
      m_spawnerTimer=500;
    }
  }
  for (const auto& enemy : enemies) {
    enemy->update(ctx);
  }
  removeDeadEnemies();
}

void EnemyManager::draw(const context& ctx) {
  for (const auto& enemy : enemies) {
    enemy->draw(ctx);
  }
}