#include "stdafx.h"

#include "../Calculator/Calculator.h"

using namespace std;

TEST_CASE("Var tests")
{
	SECTION("Set var")
	{
		CCalculator variable;
		variable.Var("x");
		CHECK(variable.Var("x") == "This variable is already exist");
	}
	SECTION("Set let")
	{
	}
}
