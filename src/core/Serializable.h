#pragma once
#include <nlohmann/json.hpp>

using nlohmann::json;

class Serializable
{
public:
	virtual ~Serializable() = default;
	virtual json serialize() = 0;
};