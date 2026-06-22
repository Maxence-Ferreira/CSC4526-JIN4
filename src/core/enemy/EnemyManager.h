#pragma once
#include <vector>
#include <queue>

#include "Enemy.h"
#include "../map/Terrain.h"
#include "../Drawable.h"
#include <sstream>
#include "Serializable.h"


enum class EnemyType {
    Cyrano, Kamikaze, HorseSoldier, Dog, FirearmSoldier, MeleeSoldier
};

class EnemyManager : public Drawable,public Serializable{
 private:
  std::vector<std::unique_ptr<Enemy>> enemies;
  int waveNumber;
  int m_difficulty;
  std::queue<EnemyType> m_spawner;
  float m_spawnerTimer;
  Terrain* m_terrain;
  sf::Font m_font;
  sf::Text m_text_displayer;
  int m_pending_bounties;
  

 public:
	EnemyManager(int difficulty);
	EnemyManager(json& glob,json& save);
	virtual ~EnemyManager() = default;

  void spawnEnemy(EnemyType type);
  void newWave(Terrain* terrain);
  void loadWave(Terrain* terrain, json& save);
	virtual void draw(const context& ctx)override;
	virtual void update(const context& ctx) override;
	void removeDeadEnemies();
	int getWaveNumber() const { return waveNumber; };
	int getDifficulty() const {return m_difficulty; };
  void drawWave(const context& ctx);
  int collectBounties();

  // Hérité via Serializable
  virtual void serialize(json& glob, json& output) override;
};