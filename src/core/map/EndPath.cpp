#include "EndPath.h"

EndPath::EndPath(int x, int y):Path(x,y)
{
}

void EndPath::update(const context& ctx)
{
	repath();
	Path::update(ctx);
}
