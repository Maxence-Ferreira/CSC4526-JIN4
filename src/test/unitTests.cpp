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
	terter.getPaths();
}

TEST(TerrainTest, PathfindingIsFullyConnected) {
	std::mt19937 gen(42);
    int width = 20;
    int height = 15;
    
    // 1. On génère le terrain
    Terrain terrain(width, height, 3, gen);
    const auto& entries = terrain.getEntry();
    
    // On s'assure qu'il y a bien des entrées générées
    ASSERT_FALSE(entries.empty()) << "Le terrain n'a genere aucune entree !";

    int expectedEndX = width - 2;
    int expectedEndY = height / 2;

    // 2. On vérifie chaque chemin
    for (BeginPath* startTile : entries) {
        std::vector<Tile*> route = terrain.pathfind(startTile->getX(), startTile->getY());
        
        // Le chemin ne doit pas être vide (pas d'orphelin)
        ASSERT_FALSE(route.empty()) << "Chemin orphelin trouve aux coordonnees : " 
                                    << startTile->getX() << "," << startTile->getY();
        
        // La dernière case doit être la sortie attendue
        Tile* endTile = route.back();
        EXPECT_EQ(endTile->getX(), expectedEndX) << "Mauvaise destination X";
        EXPECT_EQ(endTile->getY(), expectedEndY) << "Mauvaise destination Y";
    }
}