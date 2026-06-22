#include "EnemyManager.h"

#include <queue>
#include <random>

#include "../map/BeginPath.h"
#include "../map/Terrain.h"
#include "Cyrano.h"
#include "Dog.h"
#include "FirearmSoldier.h"
#include "HorseSoldier.h"
#include "Kamikaze.h"
#include "MeleeSoldier.h"

EnemyManager::EnemyManager(int difficulty)
    : Drawable(),
      m_difficulty(difficulty),
      waveNumber(0),
      m_spawnerTimer(0.f),
      m_terrain(nullptr),
      m_font(),
      m_text_displayer(m_font),
      m_pending_bounties(0) {
  // pour eviter les crashs pendant les tests qui n'ont pas accès à ressource
  try {
    if (m_font.openFromFile("resources/Cyrano.ttf")) {
      m_text_displayer.setFont(m_font);
    }
  } catch (...) {
  }
}

EnemyManager::EnemyManager(json& glob, json& save) :
    Drawable(),
    m_difficulty(glob["difficulty"]),
    waveNumber(save["wave"]),
    m_spawnerTimer(save["spawnerTimer"]),
    m_pending_bounties(0),
    m_terrain(nullptr),
    m_font(),
    m_text_displayer(m_font),
    m_spawner()
{
    try {
        if (m_font.openFromFile("resources/Cyrano.ttf")) {
            m_text_displayer.setFont(m_font);
        }
    }
    catch (...) {
    }
    for (EnemyType t : save["spawner"])m_spawner.push(t);

}

static BeginPath* getRandomPath(const std::vector<BeginPath*>& path) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, path.size() - 1);
  return path[dis(gen)];
}

// crée un ensemble d'ennemis a chaque vague
void EnemyManager::newWave(Terrain* terrain) {
  m_terrain = terrain;
  waveNumber++;
  int totalEnemies = 5 + waveNumber * m_difficulty;
  std::vector<BeginPath*> entryPath = terrain->getEntry();

  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> hundredRoll(1, 100);
  std::uniform_int_distribution<> enemyTypeRoll(0, 1);  //

  // diff = {2,3,4,5,6}
  int eliteProba = std::min(
      30 * (m_difficulty / 2),
      (waveNumber - 1) * 2 *
          (m_difficulty - 1));  // elites commencent à 0% et augmentent de
                                // 2*diff% par vague (plafond à 30(*diff/2)%)
  int mediumProba =
      std::min(30 / (m_difficulty / 2),
               (waveNumber - 1) * 4 *
                   (m_difficulty -
                    1));  // elites commencent à 0% et augmentent de 4*(diff-1)%
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

  m_spawner.push(EnemyType::Cyrano);
}

void EnemyManager::loadWave(Terrain* terrain, json& save)
{
    m_terrain=(terrain);
    for (json& j : save)
    {
        Path* c = (Path*)terrain->getTile(j["x"], j["y"]);
        if (j["type"] == "Cyrano")enemies.push_back(std::make_unique<Cyrano>(j,c));
        else if (j["type"] == "Dog")enemies.push_back(std::make_unique<Dog>(j, c));
        else if (j["type"] == "FirearmSoldier")enemies.push_back(std::make_unique<FirearmSoldier>(j, c));
        else if (j["type"] == "Kamikaze")enemies.push_back(std::make_unique<Kamikaze>(j, c));
        else if (j["type"] == "MeleeSoldier")enemies.push_back(std::make_unique<MeleeSoldier>(j, c));
        else if (j["type"] == "HorseSoldier")enemies.push_back(std::make_unique<HorseSoldier>(j, c));
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
      enemies.push_back(
          std::make_unique<HorseSoldier>(getRandomPath(entryPath)));
      break;
    case EnemyType::Dog:
      enemies.push_back(std::make_unique<Dog>(getRandomPath(entryPath)));
      break;
    case EnemyType::FirearmSoldier:
      enemies.push_back(
          std::make_unique<FirearmSoldier>(getRandomPath(entryPath)));
      break;
    case EnemyType::MeleeSoldier:
      enemies.push_back(
          std::make_unique<MeleeSoldier>(getRandomPath(entryPath)));
      break;
  }
}

void EnemyManager::removeDeadEnemies() {
  for (auto it = enemies.begin(); it != enemies.end();) {
    if (!(*it)->isAlive()) {
      m_pending_bounties += (*it)->getBounty();
      it = enemies.erase(it);  // renvoie l'iterateur suivant
    } else {
      ++it;
    }
  }
}

void EnemyManager::update(const context& ctx) {
  if (!m_spawner.empty()) {
    m_spawnerTimer -= ctx.dt;
    if (m_spawnerTimer <= 0) {
      spawnEnemy(m_spawner.front());
      m_spawner.pop();
      m_spawnerTimer = 500;
    }
  }
  for (const auto& enemy : enemies) {
    enemy->update(ctx);
  }
  removeDeadEnemies();
  if (enemies.empty() && m_spawner.empty()) {
    newWave(m_terrain);
  }
}

void EnemyManager::draw(const context& ctx) {
  for (const auto& enemy : enemies) {
    enemy->draw(ctx);
  }
}

void EnemyManager::drawWave(const context& ctx) {
  std::ostringstream oss("");
  oss << "Wave  " << (int)waveNumber;
  m_text_displayer.setString(oss.str());
  m_text_displayer.setOutlineColor(sf::Color::Black);
  m_text_displayer.setOutlineThickness(2.0f);
  m_text_displayer.setPosition(sf::Vector2f(10.0f, 30.0f));
  ctx.window->draw(m_text_displayer);
  // View::draw();
}

int EnemyManager::collectBounties() {
  int res = m_pending_bounties;
  m_pending_bounties = 0;
  return res;
}

void EnemyManager::serialize(json& glob, json& output)
{
    output["wave"] = waveNumber;
    output["spawnerTimer"] = m_spawnerTimer;
    output["pendingBounties"] = m_pending_bounties;
    auto q = m_spawner;
    while(q.size())
    {
        output["spawner"].push_back(q.front());
        q.pop();
    }
}
