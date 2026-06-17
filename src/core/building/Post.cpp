#include "Post.h"

#include "SFML/Graphics.hpp"

Post::Post(Ground* g)
    : Building(g, 0, 5, 3, 1000, 0) {}

void Post::draw(const context& ctx) {
    ctx.rm->draw({ { TILE_SIZE * getX(), TILE_SIZE * getY()},{ TILE_SIZE, TILE_SIZE} }, "post");
}

void Post::update(const context& ctx) {
    //Building::update(ctx); 
}
