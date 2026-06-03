add_library(lib_core
  myMain.cpp myMain.h
  Enemy.cpp Enemy.h
  "Terrain.cpp" "Terrain.h"
  "Tile.h" "Tile.cpp"
  "Path.cpp" "Path.h" "Ground.h" "Ground.cpp" "EndPath.h" "EndPath.cpp" "BeginPath.h" "BeginPath.cpp")

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)
