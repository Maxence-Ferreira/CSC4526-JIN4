#pragma once

#include "Path.h"

class EndPath :public Path {
public:
	EndPath(int x, int y);
	virtual void update(int dt) override;
private:
protected:
};