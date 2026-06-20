#pragma once
#include <vector>
#include <queue>

#include "Enemy.h"
#include "../map/Terrain.h"
#include "../Drawable.h"
#include <sstream>


enum class EnemyType {
    Cyrano, Kamikaze, HorseSoldier, Dog, FirearmSoldier, MeleeSoldier
};

class EnemyManager : public Drawable{
 private:
  std::vector<std::unique_ptr<Enemy>> enemies;
  int waveNumber;
  int m_difficulty;
  std::queue<EnemyType> m_spawner;
  float m_spawnerTimer;
  Terrain* m_terrain;
  sf::Font m_font;
  sf::Text m_text_displayer;
  

 public:
	EnemyManager(int difficulty);
	virtual ~EnemyManager() = default;

  void spawnEnemy(EnemyType type);
	void newWave(Terrain* terrain);
	virtual void draw(const context& ctx)override;
	virtual void update(const context& ctx) override;
	void removeDeadEnemies();
	int getWaveNumber() const { return waveNumber; };
	int getDifficulty() const {return m_difficulty; };
  void drawWave(const context& ctx);
};