#include "Path.h"
#include <algorithm>
#include <queue>
#include <unordered_set>
#include "enemy/Enemy.h"

Path::Path(int x, int y) :Tile(x, y), m_neighbors{}, m_distance{ (unsigned int)(-1) }, m_next(0), m_enemies{}, m_tex("path"), m_nearest_building(0)
{
	m_tex += '1' + rand() % 4;
}

void Path::addNeighbor(Path* nei)
{
	if (!nei||std::find(m_neighbors.begin(), m_neighbors.end(),nei)!= m_neighbors.end() && nei != this)return;
	int dx = nei->m_x - m_x;
	int dy = nei->m_y - m_y;
	if (dx * dx + dy * dy != 1)return;
	m_neighbors.push_back(nei);
	nei->m_neighbors.push_back(this);
}

const std::vector<Path*>& Path::getNeighbors()
{
	return m_neighbors;
}

void Path::addDistanceFrom(Building* nei)
{
	if (m_nearest_building&& m_nearest_building->distanceTo(this) <= nei->distanceTo(this))return;
	m_nearest_building = nei;
	nei->addDistanceFrom(this);
}

Building* Path::getNearestBuilding()
{
	return m_nearest_building;
}

void Path::invalidNearestBuilding()
{
	m_nearest_building = 0;
}

Path* Path::next() const
{
	return m_next;
}

void Path::addEnemy(Enemy* enemy)
{
	m_enemies.push_back(enemy);
}

void Path::removeEnemy(Enemy* enemy)
{
	auto it = std::find(m_enemies.begin(), m_enemies.end(), enemy);
	if(it!=m_enemies.end())m_enemies.erase(it);
}

void Path::update(const context& ctx)
{/*
	for (Entity* e : m_enemies)
	{
		((Enemy*)e)->move(ctx.dt);
	}
*/
}

void Path::draw(const context& ctx)
{
	ctx.rm->draw({ {TILE_SIZE * (m_x), TILE_SIZE * (m_y)},{TILE_SIZE, TILE_SIZE } }, m_tex);
}

std::vector<Entity*> Path::getEntity() const
{
	return std::vector<Entity*>(m_enemies.begin(), m_enemies.end());
}

unsigned int Path::cost() const
{
	return 1;
}

void Path::repath()
{
	//liste tri�
	std::priority_queue<std::pair<unsigned int,Path*>,std::vector<std::pair<unsigned int, Path*>>,std::greater<>>totreat;
	totreat.push({ 0,this });
	m_distance = 0;
	while (!totreat.empty()) {
		// On prend le plus petit
		auto[dist,cur]= totreat.top();
		totreat.pop();
		if (dist > cur->m_distance)continue;
		//on update ses neighbors si ca diminue leur distance
		for (Path* p : cur->m_neighbors)
		{
			unsigned int d = dist + p->cost();
			if (d < p->m_distance)
			{
				p->m_distance = d;
				p->m_next = cur;
				totreat.push({ d,p });
			}
		}
	}
}

bool Path::hasEntity() const{
	return !m_enemies.empty();
}

void Path::serialize(json& glob, json& output)
{
	Tile::serialize(glob, output);
	output["tex"] = m_tex;
	//serialize enemies

	for (int i = 0;i<m_enemies.size();i++)
	{
		output["enemie"] = glob["enemies"].size();
		glob["enemies"].push_back(json());
		json& b = glob["enemies"].back();
		m_enemies[i]->serialize(glob, b);

	}
}
