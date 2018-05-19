#include "stdafx.h"
#include "../StringStack/CStringStack.h"

using namespace std;

const string PUSH_STRING = "string";

CStringStack InitializeStack()
{
	CStringStack stringStack;
	stringStack.Push(PUSH_STRING);
	return stringStack;
}

TEST_CASE("[CStringStack]")
{
	SECTION("push string")
	{
		auto stringStack = InitializeStack();
		REQUIRE(stringStack.GetTop() == "string");
	}
	SECTION("check the contents of the stack")
	{
		SECTION("check is empty")
		{
			CStringStack stringStack;
			REQUIRE(stringStack.IsEmpty());
		}
		SECTION("check is not empty")
		{
			auto stringStack = InitializeStack();
			REQUIRE_FALSE(stringStack.IsEmpty());
		}
	}
	SECTION("pop element")
	{
		auto stringStack = InitializeStack();
		REQUIRE_NOTHROW(stringStack.Pop());
	}

	SECTION("clear stack")
	{
		auto stringStack = InitializeStack();
		REQUIRE(!stringStack.IsEmpty());
		stringStack.Clear();
		REQUIRE(stringStack.IsEmpty());
	}

	SECTION("copy stack")
	{
		auto stringStack = InitializeStack();
		stringStack.Push("string");
		CStringStack stack(stringStack);
		REQUIRE(stack.GetTop() == stringStack.GetTop());
	}

	SECTION("copy empty stack")
	{
		CStringStack stringStack;
		REQUIRE(stringStack.IsEmpty());
		CStringStack stack(stringStack);
		REQUIRE(stack.IsEmpty());
	}

	SECTION("move stack")
	{
		auto stringStack = InitializeStack();
		CStringStack stack = std::move(stringStack);
		REQUIRE(stringStack.IsEmpty());
		REQUIRE(stack.GetTop() == PUSH_STRING);
	}

	SECTION("assign stack")
	{
		auto stringStack = InitializeStack();
		CStringStack stack;
		stack = stringStack;
		REQUIRE(stack.GetTop() == stringStack.GetTop());
	}

	SECTION("assign stack and move")
	{
		auto stringStack = InitializeStack();
		REQUIRE(!stringStack.IsEmpty());
		stringStack = CStringStack();
		REQUIRE(stringStack.IsEmpty());
	}

	SECTION("exceptions")
	{
		SECTION("pop element when stack is empty")
		{
			CStringStack stringStack;
			REQUIRE_THROWS_AS(stringStack.Pop(), std::logic_error);
		}
		SECTION("get top element when stack is empty")
		{
			CStringStack stringStack;
			REQUIRE_THROWS_AS(stringStack.GetTop(), std::logic_error);
		}
	}
}
