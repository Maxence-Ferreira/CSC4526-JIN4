#pragma once
#include "Building.h"

class Post : public Building
{
public:
	Post(Ground* tile, int pv);
	virtual void draw(const context& ctx) override;
	virtual void update(const context& ctx) override;
private:
protected:
};