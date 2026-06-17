#pragma once

#include "../common.h"
#include "View.h"

class ViewManager
{
public:
	ViewManager();
private:
	std::vector<std::unique_ptr<View>> m_views;
};