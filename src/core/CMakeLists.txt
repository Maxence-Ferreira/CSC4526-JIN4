add_library(lib_core
  "myMain.cpp" "myMain.h"
  "enemy/Enemy.cpp" "enemy/Enemy.h"
  "map/Terrain.cpp" "map/Terrain.h"
  "map/Tile.h" "map/Tile.cpp"
  "map/Path.cpp" "map/Path.h" "map/Ground.h" "map/Ground.cpp" "map/EndPath.h" "map/EndPath.cpp" "map/BeginPath.h" "map/BeginPath.cpp"
  "enemy/FirearmSoldier.cpp" "enemy/FirearmSoldier.h"
  "enemy/MeleeSoldier.cpp" "enemy/MeleeSoldier.h"
  "enemy/Cyrano.cpp" "enemy/Cyrano.h"
  "enemy/Dog.cpp" "enemy/Dog.h"
  "enemy/HorseSoldier.cpp" "enemy/HorseSoldier.h"
  "enemy/Kamikaze.cpp" "enemy/Kamikaze.h"
  "enemy/Attack.h" "enemy/Attack.cpp" "common.h"
  "enemy/EnemyManager.cpp" "enemy/EnemyManager.h" "Drawable.h" "building/Building.h" "building/Building.cpp"
   "building/Archer.h" "building/Archer.cpp"
   "Entity.h" "building/Canon.h" "building/Canon.cpp" "building/BuildingManager.h" "building/BuildingManager.cpp")

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)
