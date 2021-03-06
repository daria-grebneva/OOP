#include "stdafx.h"
#include "../TVSet/CTVSet.h"

CTVSet tv;

TEST_CASE("basic TV functions", "[CTVSet]")
{
	SECTION("is turned off by default")
	{

		REQUIRE_FALSE(tv.IsTurnedOn());
	}

	SECTION("can't select channel when turned off")
	{
		REQUIRE_FALSE(tv.SelectChannel(87));
		REQUIRE(tv.GetChannel() == 0);
	}

	SECTION("displays channel 0 by default")
	{

		REQUIRE(tv.GetChannel() == 0);
	}

	SECTION("can be turned on")
	{
		tv.TurnOn();
		REQUIRE(tv.IsTurnedOn());
	}
}

TEST_CASE("when TV turned on", "[CTVSet]")
{
	tv.TurnOn();

	SECTION("displays channel one")
	{
		REQUIRE(tv.GetChannel() == 1);
	}

	SECTION("can be turned off")
	{
		tv.TurnOff();
		REQUIRE_FALSE(tv.IsTurnedOn());
	}

	SECTION("can select channel from 1 to 99")
	{
		REQUIRE(tv.SelectChannel(1));
		REQUIRE(tv.GetChannel() == 1);

		REQUIRE(tv.SelectChannel(99));
		REQUIRE(tv.GetChannel() == 99);

		REQUIRE(tv.SelectChannel(42));
		REQUIRE(tv.GetChannel() == 42);

		REQUIRE_FALSE(tv.SelectChannel(0));
		REQUIRE(tv.GetChannel() == 42);

		REQUIRE_FALSE(tv.SelectChannel(100));
		REQUIRE(tv.GetChannel() == 42);
	}

	SECTION("can switch to the previous channel")
	{
		REQUIRE(tv.SelectChannel(90));
		REQUIRE(tv.SelectChannel(42));
		REQUIRE(tv.SelectPreviousChannel());
		REQUIRE(tv.GetChannel() == 90);
	}
}

TEST_CASE("after subsequent turning on", "[CTVSet]")
{
	tv.TurnOn();
	tv.SelectChannel(33);
	tv.TurnOff();
	tv.TurnOn();

	SECTION("restores last selected channel")
	{
		REQUIRE(tv.GetChannel() == 33);
	}
	SECTION("can switch to the previous channel")
	{
		REQUIRE(tv.SelectChannel(42));
		REQUIRE(tv.SelectPreviousChannel());
		REQUIRE(tv.GetChannel() == 33);
	}
}
