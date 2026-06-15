#include "Terrain.h"

#include "Path.h"
#include "EndPath.h"
#include "BeginPath.h"
#include "Ground.h"

#include <map>
#include <iostream>
#define calc_x(i) (1+(size_x-4)/(nrange+1)*(i))

Terrain::Terrain(int size_x, int size_y, int difficulty, std::mt19937& gen) : m_tiles((long long)size_x* (long long)size_y),m_width(size_x),m_height(size_y),m_end(0),m_inputs{}
{
	int nrange = ceil(log2(difficulty));
	for (int j = 0; j < size_y; j++)
		for (int i = 0; i < size_x; i++)
			m_tiles[j* (long long)size_x+i]=std::make_unique<Ground>(i,j);

	//cr�e la sortie
	std::unique_ptr<EndPath> endp(std::make_unique<EndPath>(size_x-2, size_y/2));
	m_end = endp.get();
	m_paths.push_back(endp.get());
	//ajout des parantheses pour size_y/2
	m_tiles[(size_x - 2) + (size_y / 2)*size_x] = std::move(endp);

	//cr�e les entr�es
	std::uniform_int_distribution<> heightRD(3, size_y-4);
	int pos;
	bool find;
	int min_ = 1;
	int max_ = size_y-2;

	std::unique_ptr<BeginPath> tmp(std::make_unique<BeginPath>(1, 1));
	std::unique_ptr<Path> p;
	for (int X = 2; X < calc_x(1); X++)
	{
		p= std::make_unique<Path>(X, 1);
		m_paths.push_back(p.get());
		m_tiles[X + 1 * size_x] = std::move(p);
	}
	m_inputs.push_back(tmp.get());
	m_paths.push_back(m_inputs.back());
	m_tiles[1 * (long long)size_x + 1] = std::move(tmp);
	tmp=(std::make_unique<BeginPath>(1, size_y-2));
	for (int X = 2; X < calc_x(1); X++)
	{
		p = std::make_unique<Path>(X, (size_y - 2));
		m_paths.push_back(p.get());
		m_tiles[X + (size_y - 2) * size_x] = std::move(p);
	}
	m_inputs.push_back(tmp.get());
	m_paths.push_back(m_inputs.back());
	m_tiles[(size_y - 2) * (long long)size_x + 1] = std::move(tmp);
	for (int i = 0; i < difficulty-2; i++)
	{
		find = true;
		while (find)
		{
			pos = heightRD(gen);
			find = false;
			for (const auto& beg : m_inputs)
			{
				if (beg->getY() - 1 <= pos && beg->getY() + 1 >= pos)
				{
					find = true;
					break;
				}
			}
		}
		std::unique_ptr<BeginPath> beg(std::make_unique<BeginPath>(1, pos));
		for (int X = 2; X < calc_x(1); X++)
		{
			p= std::make_unique<Path>(X, pos);
			m_paths.push_back(p.get());
			m_tiles[X + pos * size_x] = std::move(p);
		}
		m_inputs.push_back(beg.get());
		m_paths.push_back(beg.get());
		m_tiles[pos * (long long)size_x+1] = std::move(beg);
	}
	//cr�e les points interm�diaires et les relies

	int npoint = difficulty;
	int min = size_y-2;
	int max = 1;
	int x_ = 1;
	int x = 1;
	int y=0;
	for (int i = 1; i <= nrange; i++)
	{
		npoint = ceil((float)npoint / 2.f);
		x = calc_x(i);

		for (int j = 0; j < npoint; j++)
		{
			y= heightRD(gen);
			while (dynamic_cast<Path*>(getTile(x+1, y)) || dynamic_cast<Path*>(getTile(x+1, y-1)) || dynamic_cast<Path*>(getTile(x+1, y + 1)))
			{
				y = heightRD(gen);
			}

			//modif de la borne de la boucle à limit_x
			int limit_x=(i==nrange) ? (size_x -3):calc_x(i+1);

			for (int X = x + 1; X < limit_x; X++)
			{
				p = std::make_unique<Path>(X, y);
				m_paths.push_back(p.get());
				m_tiles[X + y * size_x] = std::move(p);
			}
			min = (min < y) ? min : y;
			max = (max > y) ? max : y;
		}
		for (int Y = min_; Y <= max_; Y++)
		{
			p = std::make_unique<Path>(x, Y);
			m_paths.push_back(p.get());
			m_tiles[x + Y * size_x] = std::move(p);
		}

		max_ = max;
		min_ = min;
		heightRD= std::uniform_int_distribution<>(min_, max_);
		min = max_;
		max = min_;
		x_ = x;
	}
	for (
		int Y = ((y < size_y / 2) ? y : (size_y / 2));	// min entre la fin du chemin et le dernier tile plac�
		Y <= ((y > size_y / 2) ? y : (size_y / 2));		// max entre ...
		Y++)
	{
		p = std::make_unique<Path>(size_x - 3, Y);
		m_paths.push_back(p.get());
		m_tiles[size_x - 3 + Y * size_x] = std::move(p);
	}
	//link paths
	for (auto it = m_paths.begin(); it != m_paths.end(); it++)
		for (auto it2 = it+1; it2 != m_paths.end(); it2++)
			(*it)->addNeighbor(*it2);//auto eject non neighbor case 
	m_end->update({});
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

void Terrain::update(const context& ctx)
{
	if(m_end)m_end->update(ctx);
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

void Terrain::addBuilding(Building* ptr) const
{
	for (Path* p : m_paths)p->addDistanceFrom(ptr);
}

Tile* Terrain::getTile(int x, int y) const
{
	return m_tiles[y * (long long)m_width + x].get();
}
