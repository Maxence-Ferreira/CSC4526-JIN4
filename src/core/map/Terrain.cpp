#include "Terrain.h"

#include "Path.h"
#include "EndPath.h"
#include "BeginPath.h"
#include "Ground.h"

#include <map>
#include <random>
#include <iostream>

Terrain::Terrain(int size_x, int size_y, int difficulty) : m_tiles((long long)size_x* (long long)size_y),m_width(size_x),m_height(size_y),m_end(0),m_inputs{}
{
	std::vector<Path*> paths;
	for (int j = 0; j < size_y; j++)
		for (int i = 0; i < size_x; i++)
			m_tiles[j* (long long)size_x+i]=std::make_unique<Ground>(i,j);

	//crée la sortie
	std::unique_ptr<EndPath> endp(std::make_unique<EndPath>(size_x-2, size_y/2));
	m_end = endp.get();
	m_tiles[size_x - 2 + size_x * size_y / 2] = std::move(endp);

	//crée les entrées
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> heightRD(0, size_y-1);
	int pos;
	bool find;
	int min_ = size_y;
	int max_ = 0;
	for (int i = 0; i < difficulty; i++)
	{
		pos = heightRD(gen);
		find = false;
		for (const auto& beg : m_inputs)
		{
			if (beg->getY() == pos)
			{
				find = true;
				break;
			}
		}
		if (find)
		{
			i--;
			continue;
		}
		min_ = min_ < pos ? min_ : pos;
		max_ = max_ > pos ? max_ : pos;
		std::unique_ptr<BeginPath> beg(std::make_unique<BeginPath>(1, pos));
		m_inputs.push_back(beg.get());
		m_tiles[pos * (long long)size_x+1] = std::move(beg);
	}
	//crée les points intermédiaires et les relies

	int nrange = ceil(log2(difficulty));
	float dx = (size_x - 4 - nrange) / (float)(nrange + 1);

	int npoint = difficulty;
	int min = size_y;
	int max = 0;
	int x_ = 1;
	int x = 1;
	int y;
	for (int i = 0; i < nrange; i++)
	{
		npoint = ceil((float)npoint / 2.f);
		x += dx;

		for (int j = 0; j < npoint; j++)
		{
			y= heightRD(gen);
			if (dynamic_cast<Path*>(getTile(x, y)))
			{
				j--;
				continue;
			}
			for(int X=x+1;X<x+dx;X++)
				m_tiles[X + y * size_x] = std::make_unique<Path>(X, y);
			min = (min < y) ? min : y;
			max = (max > y) ? max : y;
		}
		std::cout << min << " " << max << std::endl;
		for (int Y = min; Y <= max; Y++)
			m_tiles[x + dx + Y * size_x] = std::make_unique<Path>(x + dx, Y);

		max_ = max;
		min_ = min;
		min = size_y;
		max = 0;
		x_ = x;
	}

	for (int X = x_ + 1; X < size_x-2; X++)
		m_tiles[X + m_end->getY() * size_x] = std::make_unique<Path>(X, m_end->getY());

	//link paths
	for (auto it = paths.begin(); it != paths.end(); it++)
		for (auto it2 = it+1; it2 != paths.end(); it2++)
			(*it)->addNeighbor(*it2);//auto eject non neighbor case 
}

int Terrain::getWidth() const
{
	return m_width;
}

int Terrain::getHeight() const
{
	return m_height;
}

const std::vector<BeginPath*>& Terrain::getEntry() const
{
	return m_inputs;
}

void Terrain::draw(const context& ctx)
{
	for (const auto& i : m_tiles)
	{

		i->draw(ctx);

	}
}

void Terrain::update(int dt)
{
	if(m_end)m_end->update(dt);
}

std::vector<Tile*> Terrain::pathfind(int from_x, int from_y) const
{
	Path* p=dynamic_cast<Path*>(m_tiles[from_y * (long long)m_width + from_x].get());
	if(!p)
		return std::vector<Tile*>();
	std::vector<Tile*>r{ p };
	while (p->next()) {
		p = p->next();
		r.push_back(p);
	}
	return r;
}

Tile* Terrain::getTile(int x, int y) const
{
	return m_tiles[y * (long long)m_width + x].get();
}
