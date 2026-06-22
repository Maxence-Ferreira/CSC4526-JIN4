#include "Post.h"

#include "SFML/Graphics.hpp"

Post::Post()
    : Building(0, 5, 3, 1000, 0) {}

Post::Post(json& save):Building(save)
{
}

void Post::draw(const context& ctx) {
    ctx.rm->draw({ { TILE_SIZE * getX(), TILE_SIZE * getY()},{ TILE_SIZE, TILE_SIZE} }, "post");
}

void Post::update(const context& ctx) {
    //Building::update(ctx); 
}

void Post::serialize(json& glob, json& output)
{
    Building::serialize(glob,output);
    output["type"] = "Post";
}

std::unique_ptr<Building> Post::clone(Ground* ground)
{
    std::unique_ptr<Post> ptr(std::make_unique<Post>(*this));
    ptr->setOnTile(ground);
    return std::move(ptr);
}


std::unique_ptr<Building> Post::clone()
{
    return std::make_unique<Post>(*this);
}
