#include "stdafx.h"
#include "../Calculator/CCalculatorController.h"
#include "../Calculator/СIdentifier.h"

using namespace std;
TEST_CASE(" ", "[Calculator]")
{

	struct CalculatorFixture
	{

		stringstream input;
		stringstream output;
		CCalculatorController calculator;
		CalculatorFixture()
			: calculator(input, output)
		{
		}
		void VerifyCommandHandling(string& command, const string& expectedOutput)
		{
			output = stringstream();
			input = stringstream();
			REQUIRE(input << command);
			calculator.ProcessCommand();
			REQUIRE(output.str() == expectedOutput);
		}
	};

	CalculatorFixture fixture;

	SECTION("Declaring, assigning, and outputting variable values")
	{
		string command = "var x";
		fixture.VerifyCommandHandling(command, "");
		command = "print x";
		fixture.VerifyCommandHandling(command, "-nan(ind)\n");
		command = "let x=42";
		fixture.VerifyCommandHandling(command, "");
		command = "print x";
		fixture.VerifyCommandHandling(command, "42.00\n");
		command = "let x=1.234";
		fixture.VerifyCommandHandling(command, "");
		command = "print x";
		fixture.VerifyCommandHandling(command, "1.23\n");
		command = "let y=x";
		fixture.VerifyCommandHandling(command, "");
		command = "let x=99";
		fixture.VerifyCommandHandling(command, "");
		command = "printvars";
		fixture.VerifyCommandHandling(command, "x 99.00\ny 1.23\n");
	}

	SECTION("Declaring functions")
	{
		string command = "var x";
		fixture.VerifyCommandHandling(command, "");
		command = "var y";
		fixture.VerifyCommandHandling(command, "");
		command = "fn XPlusY=x+y";
		fixture.VerifyCommandHandling(command, "");
		command = "print XPlusY";
		fixture.VerifyCommandHandling(command, "-nan(ind)\n");
		command = "let x=3";
		fixture.VerifyCommandHandling(command, "");
		command = "let y=4";
		fixture.VerifyCommandHandling(command, "");
		command = "print XPlusY";
		fixture.VerifyCommandHandling(command, "7.00\n");
		command = "let x=10";
		fixture.VerifyCommandHandling(command, "");
		command = "print XPlusY";
		fixture.VerifyCommandHandling(command, "14.00\n");
		command = "let z=3.5";
		fixture.VerifyCommandHandling(command, "");
		command = "fn XPlusYDivZ=XPlusY/z";
		fixture.VerifyCommandHandling(command, "");
		command = "printfns";
		fixture.VerifyCommandHandling(command, "XPlusY 14.00\nXPlusYDivZ 4.00\n");
	}

	SECTION("The difference between fn and let")
	{
		string command = "let v=42";
		fixture.VerifyCommandHandling(command, "");
		command = "let variable=v";
		fixture.VerifyCommandHandling(command, "");
		command = "fn function=v";
		fixture.VerifyCommandHandling(command, "");
		command = "let v=43";
		fixture.VerifyCommandHandling(command, "");
		command = "print variable";
		fixture.VerifyCommandHandling(command, "42.00\n");
		command = "print function";
		fixture.VerifyCommandHandling(command, "43.00\n");
	}

	SECTION("Calculating the area of ​​a circle")
	{
		string command = "var radius";
		fixture.VerifyCommandHandling(command, "");
		command = "let pi=3.14159265";
		fixture.VerifyCommandHandling(command, "");
		command = "fn radiusSquared=radius*radius";
		fixture.VerifyCommandHandling(command, "");
		command = "fn circleArea=pi*radiusSquared";
		fixture.VerifyCommandHandling(command, "");
		command = "let radius=10";
		fixture.VerifyCommandHandling(command, "");
		command = "print circleArea";
		fixture.VerifyCommandHandling(command, "314.16\n");
		command = "let circle10Area=circleArea";
		fixture.VerifyCommandHandling(command, "");
		command = "let radius=20";
		fixture.VerifyCommandHandling(command, "");
		command = "let circle20Area=circleArea";
		fixture.VerifyCommandHandling(command, "");
		command = "printfns";
		fixture.VerifyCommandHandling(command, "circleArea 1256.64\nradiusSquared 400.00\n");
		command = "printvars";
		fixture.VerifyCommandHandling(command, "circle10Area 314.16\ncircle20Area 1256.64\npi 3.14\nradius 20.00\n");
	}

	SECTION("Calculating the Fibonacci sequence")
	{
		string command = "let v0=0";
		fixture.VerifyCommandHandling(command, "");
		command = "let v1=1";
		fixture.VerifyCommandHandling(command, "");
		command = "fn fib0=v0";
		fixture.VerifyCommandHandling(command, "");
		command = "fn fib1=v1";
		fixture.VerifyCommandHandling(command, "");
		command = "fn fib2=fib1+fib0";
		fixture.VerifyCommandHandling(command, "");
		command = "fn fib3=fib2+fib1";
		fixture.VerifyCommandHandling(command, "");
		command = "fn fib4=fib3+fib2";
		fixture.VerifyCommandHandling(command, "");
		command = "fn fib5=fib4+fib3";
		fixture.VerifyCommandHandling(command, "");
		command = "fn fib6=fib5+fib4";
		fixture.VerifyCommandHandling(command, "");
		command = "printfns";
		fixture.VerifyCommandHandling(command, "fib0 0.00\nfib1 1.00\nfib2 1.00\nfib3 2.00\nfib4 3.00\nfib5 5.00\nfib6 8.00\n");
		command = "let v0=1";
		fixture.VerifyCommandHandling(command, "");
		command = "let v1=1";
		fixture.VerifyCommandHandling(command, "");
		command = "printfns";
		fixture.VerifyCommandHandling(command, "fib0 1.00\nfib1 1.00\nfib2 2.00\nfib3 3.00\nfib4 5.00\nfib5 8.00\nfib6 13.00\n");
	}
}
