#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"
#include "../FindMaxEx_tests/Sportsman.h"

using namespace std;

const Sportsman sportsman1 = { "Niina Aaltonen", 60.8, static_cast<float>(175.62) };
const Sportsman sportsman2 = { "Mike Adams", 80.5, static_cast<float>(186.7) };
const Sportsman sportsman3 = { "Dino Aguilar", 96.8, static_cast<float>(190.32) };

const std::vector<Sportsman> sportsmans = { sportsman1, sportsman2, sportsman3 };

Sportsman man;

TEST_CASE("[FindMaxEx]")
{
	SECTION("empty vector")
	{
		std::vector<Sportsman> emptyVector;
		REQUIRE(emptyVector.empty());
		REQUIRE(!FindMaxEx(emptyVector, man, IsLessInWeight));
		REQUIRE(!FindMaxEx(emptyVector, man, IsLessInHeight));
		REQUIRE(!FindMaxEx(emptyVector, man, IsLessInName));
	}

	SECTION("find max string name")
	{
		std::string maxName = sportsman1.name;
		REQUIRE(FindMaxEx(sportsmans, man, IsLessInName));
		REQUIRE(man.name == maxName);
	}

	SECTION("find max double weight")
	{
		double maxWeight = sportsman3.weight;
		REQUIRE(FindMaxEx(sportsmans, man, IsLessInWeight));
		REQUIRE(man.weight == maxWeight);
	}

	SECTION("find max float height")
	{
		float maxHeight = sportsman2.height;
		REQUIRE(FindMaxEx(sportsmans, man, IsLessInHeight));
		REQUIRE(man.height == maxHeight);
	}
}
