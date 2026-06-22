#include "BeginPath.h"

BeginPath::BeginPath(int x, int y):Path(x,y)
{
}

BeginPath::BeginPath(json& inp) : Path(inp)
{
}
