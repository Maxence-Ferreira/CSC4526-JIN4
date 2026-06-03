#include "EndPath.h"

EndPath::EndPath(int x, int y):Path(x,y)
{
}

void EndPath::update(int dt)
{
	repath();
	Path::update(dt);
}
