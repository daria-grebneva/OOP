#include "stdafx.h"
#include "../Rational/CRational.h"

using namespace std;

void CheckValue(CRational const& rationalNumber, int numerator, int denominator)
{
	REQUIRE(rationalNumber.GetNumerator() == numerator);
	REQUIRE(rationalNumber.GetDenominator() == denominator);
}

TEST_CASE(" ", "[CRational]")
{

	SECTION("Declare rational number without parameter")
	{
		CheckValue(CRational(), 0, 1);
	}

	SECTION("Declare rational number with numerator only")
	{
		CheckValue(CRational(5), 5, 1);
		CheckValue(CRational(-50), -50, 1);
	}

	SECTION("Declare rational number with numerator and denominator")
	{
		SECTION("Denominator less than 0")
		{
			CheckValue(CRational(5, -4), -5, 4);
		}
		SECTION("Denominator is 0")
		{
			CheckValue(CRational(5, 0), 0, 1);
		}
		SECTION("Denominator more than 0")
		{
			CheckValue(CRational(5, 4), 5, 4);
		}
	}

	SECTION("CRational can convert rational number to double")
	{
		REQUIRE(CRational(5, 2).ToDouble() == 2.5);
		REQUIRE(CRational(0, 5).ToDouble() == 0.0);
		REQUIRE(CRational(1, -3).ToDouble() == (static_cast<double>(-1) / static_cast<double>(3)));
	}

	SECTION("Unary operations")
	{
		SECTION("Unary '+' returns equal number")
		{
			CRational number(10, 3);
			number = +number;
			CheckValue(number, 10, 3);
		}

		SECTION("Unary '-' returns number with opposite sign")
		{
			CRational number(10, 3);
			number = -number;
			CheckValue(number, -10, 3);
		}
	}

	SECTION("Binary operations")
	{
		SECTION("Binary '+'")
		{
			SECTION("rational + rational")
			{
				CRational number1(1, 2);
				CRational number2(1, 4);

				number2 = number1 + number2;
				CheckValue(number2, 3, 4);
			}

			SECTION("rational + integer")
			{
				CRational number1(1, 4);

				number1 = number1 + 1;
				CheckValue(number1, 5, 4);
			}

			SECTION("integer + rational")
			{
				CRational number1(1, 2);

				number1 = 1 + number1;
				CheckValue(number1, 3, 2);
			}
		}
		SECTION("Binary '-'")
		{
			SECTION("rational- rational")
			{
				CRational number1(1, 2);
				CRational number2(3, 2);

				number1 = number1 - number2;
				CheckValue(number1, -1, 1);
			}
			SECTION("rational - integer")
			{
				CRational number1(1, 2);

				number1 = number1 - 1;
				CheckValue(number1, -1, 2);
			}

			SECTION("integer - rational")
			{
				CRational number1(1, 2);

				number1 = 1 - number1;
				CheckValue(number1, 1, 2);
			}
		}
	}
	SECTION("Increase rational '+=' ")
	{
		SECTION("with rational")
		{
			CRational number1(1, 2);
			CRational number2(1, 3);

			number1 += number2;
			CheckValue(number1, 5, 6);
		}

		SECTION("with integer")
		{
			CRational number1(1, 2);

			number1 += 1;
			CheckValue(number1, 3, 2);
		}
	}

	SECTION("Decrease rational '-=' ")
	{
		SECTION("with rational")
		{
			CRational number1(1, 2);
			CRational number2(1, 6);

			number1 -= number2;
			CheckValue(number1, 1, 3);
		}

		SECTION("with integer")
		{
			CRational number(1, 2);

			number -= 1;
			CheckValue(number, -1, 2);
		}
	}

	SECTION("Operation '*'")
	{
		SECTION("rational * rational")
		{
			CRational number1(1, 2);
			CRational number2(2, 3);

			number1 = number1 * number2;
			CheckValue(number1, 1, 3);
		}

		SECTION("rational * integer")
		{
			CRational number(1, 2);

			number = number * -3;
			CheckValue(number, -3, 2);
		}

		SECTION("integer * rational")
		{
			CRational number(2, 3);

			number = 2 * number;
			CheckValue(number, 4, 3);
		}
	}

	SECTION("Operation '/'")
	{
		SECTION("rational / rational")
		{
			CRational number1(1, 2);
			CRational number2(2, 3);

			number1 = number1 / number2;
			CheckValue(number1, 3, 4);
		}

		SECTION("rational / integer")
		{
			CRational number(1, 2);

			number = number / 3;
			CheckValue(number, 1, 6);
		}

		SECTION("integer / rational")
		{
			CRational number(2, 3);

			number = 7 / number;
			CheckValue(number, 21, 2);
		}
	}

	SECTION("Operation '*='")
	{
		SECTION("rational and integer")
		{
			CRational number1(1, 2);
			CRational number2(2, 3);

			number1 *= number2;
			CheckValue(number1, 1, 3);
		}

		SECTION("integer and rational")
		{
			CRational number1(3, 2);

			number1 *= 4;
			CheckValue(number1, 6, 1);
		}
	}

	SECTION("Operation '/='")
	{
		SECTION("rational and integer")
		{
			CRational number1(1, 2);
			CRational number2(2, 3);

			number1 /= number2;
			CheckValue(number1, 3, 4);
		}

		SECTION("integer and rational")
		{
			CRational number1(1, 2);

			number1 /= 3;
			CheckValue(number1, 1, 6);
		}
	}

	SECTION("Operation '=='")
	{
		SECTION("rational and rational")
		{
			CRational number1(1, 2);
			CRational number2(6, 2);

			REQUIRE(number1 == number1);
			REQUIRE_FALSE(number1 == number2);
		}

		SECTION("integer and rational")
		{
			CRational number(4);

			REQUIRE(4 == number);
			REQUIRE_FALSE(99 == number);
		}
	}

	SECTION("Operation '!='")
	{
		SECTION("rational and rational")
		{
			CRational number1(4);
			CRational number2(46, 123);

			REQUIRE(number1 != number2);
			REQUIRE_FALSE(number1 != number1);
		}

		SECTION("integer and rational")
		{
			CRational number(1);

			REQUIRE(4 != number);
			REQUIRE_FALSE(1 != number);
		}

		SECTION("rational and integer")
		{
			CRational number(1);

			REQUIRE(number != 4);
			REQUIRE_FALSE(number != 1);
		}
	}

	SECTION("Operation '<'")
	{
		SECTION("rational and rational")
		{
			CRational number1(1, 32);
			CRational number2(1, 2);
			CRational number3(5);

			REQUIRE(number1 < number2);
			REQUIRE_FALSE(number3 < number2);
		}

		SECTION("rational and integer")
		{
			CRational number(1, 32);

			REQUIRE(number < 1);
			REQUIRE_FALSE(number < -10);
		}

		SECTION("integer and rational")
		{
			CRational number(1, 32);

			REQUIRE(0 < number);
			REQUIRE_FALSE(10 < number);
		}
	}

	SECTION("Operation '<='")
	{
		SECTION("rational and rational")
		{
			CRational number1(1, 32);
			CRational number2(1, 2);
			CRational number3(5);

			REQUIRE(number1 <= number2);
			REQUIRE_FALSE(number3 <= number2);
		}

		SECTION("rational and integer")
		{
			CRational number(1, 32);

			REQUIRE(number <= 1);
			REQUIRE_FALSE(number <= -10);
		}

		SECTION("integer and rational")
		{
			CRational number(1, 32);

			REQUIRE(0 <= number);
			REQUIRE_FALSE(10 <= number);
		}
	}

	SECTION("Operation '>'")
	{
		SECTION("rational and rational")
		{
			CRational number1(1, 32);
			CRational number2(1, 2);
			CRational number3(5);

			REQUIRE(number3 > number2);
			REQUIRE_FALSE(number1 > number2);
		}

		SECTION("rational and integer")
		{
			CRational number1(1, 32);
			CRational number2(5);

			REQUIRE_FALSE(number1 > 1);
			REQUIRE(number2 > 1);
		}

		SECTION("integer and rational")
		{
			CRational number1(1, 32);
			CRational number2(1, 32);

			REQUIRE_FALSE(0 > number1);
			REQUIRE(5 > number2);
		}
	}

	SECTION("Operation '>='")
	{
		SECTION("rational and rational")
		{
			CRational number1(1, 32);
			CRational number2(1, 2);
			CRational number3(12, 1);

			REQUIRE_FALSE(number1 >= number2);
			REQUIRE(number3 >= number2);
		}

		SECTION("rational and integer")
		{
			CRational number(1, 32);

			REQUIRE_FALSE(number >= 32);
			REQUIRE(number >= 0);
		}

		SECTION("integer and rational")
		{
			CRational number(1, 32);

			REQUIRE_FALSE(0 >= number);
			REQUIRE(1 >= number);
		}
	}
}
