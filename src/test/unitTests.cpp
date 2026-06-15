#include <gtest/gtest.h>

#include <string>
#include <random>
#include "map/Terrain.h"
#include "map/Path.h"
#include "map/BeginPath.h"
#include "map/EndPath.h"

TEST(TERRAIN, PathOK) {
	std::random_device rd;
	std::mt19937 rand(rd());
	Terrain terter(50,50,5, rand);
	terter.m_paths;
}