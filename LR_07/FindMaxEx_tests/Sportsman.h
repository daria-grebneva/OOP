#pragma once
#include "stdafx.h"

struct Sportsman
{
	std::string name;
	double weight;
	float height;
};

bool IsLessInWeight(Sportsman const& first, Sportsman const& second)
{
	return (first.weight < second.weight);
}

bool IsLessInHeight(Sportsman const& first, Sportsman const& second)
{
	return (first.height < second.height);
}

bool IsLessInName(Sportsman const& first, Sportsman const& second)
{
	return (first.name < second.name);
}
