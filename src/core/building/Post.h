#pragma once
#include "Building.h"

class Post : public Building
{
public:
	Post();
	virtual void draw(const context& ctx) override;
	virtual void update(const context& ctx) override;
	virtual void serialize(json& glob, json& output)override;
private:
protected:

	// Hérité via Building
	virtual std::unique_ptr<Building> clone(Ground* ground) override;
	virtual std::unique_ptr<Building> clone() override;
};