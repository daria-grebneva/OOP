#include "stdafx.h"

#include "../Calculator/CalculatorController.h"

using namespace std;

TEST_CASE("Var tests")
{
	SECTION("Set var")
	{
		CCalculatorController variable;
		CHECK(variable.CreateVar("x") == "This variable is already exist");
	}
	SECTION("Set let")
	{
	}
}
