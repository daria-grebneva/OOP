#include "stdafx.h"

#include "../Calculator/Calculator.h"
#include "../Calculator/Function.h"
#include "../Calculator/Variable.h"

using namespace std;

TEST_CASE("Get names")
{
	SECTION("Get name of variable")
	{
		CVariable arg("x");
		CHECK(arg.GetName() == "x");
	}
	SECTION("Get name of function")
	{
		CFunction function("XPlusY");
		CHECK(function.GetName() == "XPlusY");
	}
}
