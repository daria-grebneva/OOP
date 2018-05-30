#include "stdafx.h"
#include "../CMyArray/CMyArray.h"

using namespace std;

struct ArrayItem
{
	ArrayItem(int value = 0)
		: value(value)
	{
	}
	int value;
};

struct EmptyArray
{
	CMyArray<ArrayItem> arr;
};

template <typename T = default>
void CheckArraysEquality(CMyArray<T>& a, CMyArray<T>& b)
{
	REQUIRE(a.GetSize() == b.GetSize());
	for (size_t i = 0; i < a.GetSize(); ++i)
	{
		REQUIRE(a[i].value == b[i].value);
	}
}

CMyArray<ArrayItem> FillArray()
{
	CMyArray<ArrayItem> arr;
	for (auto i = 0; i <= 6; ++i)
	{
		arr.Append(i);
	}
	return arr;
}

TEST_CASE("[CMyArray]")
{
	SECTION("Empty string array")
	{
		SECTION("by default array is empty")
		{
			CMyArray<ArrayItem> arr;
			REQUIRE(arr.GetSize() == 0u);
		}
		SECTION("by default array has 0 capacity")
		{
			CMyArray<ArrayItem> arr;
			REQUIRE(arr.GetCapacity() == 0u);
		}
	}
	SECTION("After appending an item into array")
	{
		SECTION("Increased size and capacity")
		{
			CMyArray<ArrayItem> arr;
			arr.Append(ArrayItem());
			REQUIRE(arr.GetSize() == 1u);
			REQUIRE(arr.GetCapacity() == 1u);
			arr.Append(ArrayItem());
			REQUIRE(arr.GetSize() == 2u);
			REQUIRE(arr.GetCapacity() == 2u);
			arr.Append(ArrayItem());
			REQUIRE(arr.GetSize() == 3u);
			REQUIRE(arr.GetCapacity() == 4u);
			arr.Append(ArrayItem());
			REQUIRE(arr.GetSize() == 4u);
			REQUIRE(arr.GetCapacity() == 4u);
		}
		SECTION("Can take back data")
		{
			CMyArray<ArrayItem> arr;
			arr.Append(1);
			REQUIRE(arr.GetBack().value == 1);
			arr.Append(2);
			REQUIRE(arr.GetBack().value == 2);
			arr.Append(3);
			REQUIRE(arr.GetBack().value == 3);
			arr.Append(4);
			REQUIRE(arr.GetBack().value == 4);
		}
	}
	SECTION("Filled array")
	{
		SECTION("Copy array")
		{
			auto arr = FillArray();
			auto copy(arr);
			REQUIRE(copy.GetSize() == arr.GetSize());
			REQUIRE(copy.GetCapacity() == arr.GetSize());
		}
		SECTION("Move array")
		{
			auto arr = FillArray();
			auto arrBackup(arr);

			auto movedArray(move(arr));

			CheckArraysEquality(movedArray, arrBackup);
			REQUIRE(arr.GetSize() == 0);
		}
		SECTION("Array indexes")
		{
			SECTION("Can take an element by index")
			{
				auto arr = FillArray();
				REQUIRE(arr[4].value == 4);
				arr[4].value = 365;
				REQUIRE(arr[4].value == 365);
			}
			SECTION("Throw exception when index out of range")
			{
				auto arr = FillArray();
				REQUIRE_THROWS_AS(arr[10], std::out_of_range);
			}
		}
		SECTION("Resize array")
		{
			auto arr = FillArray();
			arr.Resize(2);
			REQUIRE(arr.GetSize() == 2);
			arr.Resize(10);
			REQUIRE(arr.GetSize() == 10);
			for (size_t i = 2; i < 10; ++i)
			{
				REQUIRE(arr[i].value == 0);
			}
		}
		SECTION("Clear array")
		{
			auto arr = FillArray();
			REQUIRE_FALSE(arr.GetSize() == 0);
			arr.Clear();
			REQUIRE(arr.GetSize() == 0);
			REQUIRE_THROWS_AS(arr[0], std::out_of_range);
		}
		SECTION("Assign an array")
		{
			auto arr = FillArray();
			CMyArray<ArrayItem> arrForCopy;
			arrForCopy = arr;

			CheckArraysEquality(arrForCopy, arr);
		}
		SECTION("Assign an array with a move")
		{
			auto arr = FillArray();
			CMyArray<ArrayItem> arrBackup(arr);
			CMyArray<ArrayItem> arrayForMove;
			arrayForMove = move(arr);

			CheckArraysEquality(arrayForMove, arrBackup);
			REQUIRE(arr.GetSize() == 0);
		}

		SECTION("Assign an array to itself")
		{
			auto arr = FillArray();
			auto arrBackup = arr;
			auto oldCapacity = arr.GetCapacity();

			arr = arr;
			REQUIRE(oldCapacity == arr.GetCapacity());
			CheckArraysEquality(arrBackup, arr);

			arr = move(arr);
			REQUIRE(oldCapacity == arr.GetCapacity());
			CheckArraysEquality(arrBackup, arr);
		}
	}
	SECTION("Array has a iterative access")
	{
		SECTION("With the begin method")
		{
			auto arr = FillArray();
			auto it = arr.begin();
			REQUIRE((*it).value == 0);
			++it;
			++it;
			REQUIRE((*it).value == 2);
			--it;
			REQUIRE((*it).value == 1);
		}
		SECTION("With the end method")
		{
			auto arr = FillArray();
			auto it = arr.end();
			--it;
			REQUIRE((*it).value == 6);
			--it;
			--it;
			REQUIRE((*it).value == 4);
			++it;
			REQUIRE((*it).value == 5);
		}
		SECTION("With the rbegin method")
		{
			auto arr = FillArray();
			auto it = arr.rbegin();
			REQUIRE((*it).value == 6);
			++it;
			++it;
			REQUIRE((*it).value == 4);
			--it;
			REQUIRE((*it).value == 5);
		}
		SECTION("With the rend method")
		{
			auto arr = FillArray();
			auto it = arr.rend();
			--it;
			REQUIRE((*it).value == 0);
			--it;
			--it;
			REQUIRE((*it).value == 2);
			++it;
			REQUIRE((*it).value == 1);
		}
	}
}
