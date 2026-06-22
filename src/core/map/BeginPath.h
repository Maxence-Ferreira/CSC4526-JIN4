#pragma once

#include "Path.h"

class BeginPath :public Path {
public:
	BeginPath(int x, int y);
	BeginPath(json& inp);
private:
protected:
};