#pragma once
#include <nlohmann/json.hpp>

using nlohmann::json;

class Serializable
{
public:
	virtual ~Serializable() = default;
	virtual void serialize(json& output) = 0;
};