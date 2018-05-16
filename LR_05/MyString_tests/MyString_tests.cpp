#include "stdafx.h"

#include "../MyString/CMyString.h"

using namespace std;

int StringSize(const char* str)
{
	int sizeStr = 0;
	while (str[sizeStr] != '\0')
	{
		sizeStr++;
	}
	return sizeStr;
}

void CompareStringsContents(const CMyString& str1, const char* str2, size_t strSize)
{
	auto myStr = str1.GetStringData();
	for (int i = 0; i < strSize; ++i)
	{
		REQUIRE(myStr[i] == str2[i]);
	}
}

void CompareNotIdenticalStrings(const CMyString& str1, const char* str2, size_t strSize)
{
	auto myStr = str1.GetStringData();
	for (int i = 0; i < strSize; ++i)
	{
		if (myStr[i] != str2[i])
		{
			REQUIRE_FALSE(myStr[i] == str2[i]);
		}
	}
}

TEST_CASE(" ", "[My String]")
{

	SECTION("Create a normal string")
	{
		SECTION("String without parameters")
		{
			CMyString str;
			REQUIRE(str.GetLength() == 0);
			CompareStringsContents(str, "", 0);
		}
		SECTION("String with empty string")
		{
			CMyString str1("");
			REQUIRE(str1.GetLength() == 0);
			CompareStringsContents(str1, "", 0);
			CMyString str2("", 0);
			REQUIRE(str2.GetLength() == 0);
			CompareStringsContents(str2, "", 0);
		}

		SECTION("With usual data")
		{
			CMyString str1("Normal string!");
			REQUIRE(str1.GetLength() == 14);
			CompareStringsContents(str1, "Normal string!", 14);
		}
		SECTION("With stl library")
		{
			string str2 = "Normal string!";
			CMyString str3(str2);
			REQUIRE(str3.GetLength() == str2.size());
		}
		SECTION("By copy")
		{
			CMyString str1("Normal string!");
			CMyString str2(str1);
			REQUIRE(str1.GetLength() == str2.GetLength());
			CompareStringsContents(str2, str1.GetStringData(), str1.GetLength());
		}
	}
	SECTION("Get length of string")
	{
		CMyString str1("My string!");
		REQUIRE(str1.GetLength() == 10);
		CMyString str2("");
		REQUIRE(str2.GetLength() == 0);
		CMyString str3;
		REQUIRE(str3.GetLength() == 0);
	}
	SECTION("Get string data")
	{
		CMyString str("My string!");
		REQUIRE(str.GetStringData()[0] == str[0]);
		REQUIRE(str.GetStringData()[5] == str[5]);
		REQUIRE(str.GetStringData()[10] == '\0');
	}
	SECTION("Get substring")
	{
		CMyString str("My string!");
		REQUIRE(str.SubString(0, 1) == "M");
		REQUIRE(str.SubString(0, 10) == "My string!");
		REQUIRE(str.SubString(3, 6) == "string");
		CMyString emptyStr("");
		REQUIRE(emptyStr.SubString(0, 0) == "");
	}
	SECTION("Clear string")
	{
		CMyString str("My string!");
		CompareStringsContents(str, "My string!", 10);
		str.Clear();
		CompareStringsContents(str, "", 0);
	}

	SECTION("Check operators")
	{
		SECTION("=")
		{
			CMyString str("My string!");
			str = str;
			CompareStringsContents(str, "My string!", 10);
			CMyString str2("Other string");
			str = str2;
			CompareStringsContents(str, "Other string", 12);
		}

		SECTION("+")
		{
			CMyString str1("I love");
			CMyString str2(" OOP");
			CMyString str3("!");
			CMyString str = str1 + str2 + str3;
			CompareStringsContents(str, "I love OOP!", 11);
			string str4 = " programming!";
			CMyString str5 = str1 + str4;
			CompareStringsContents(str5, "I love programming!", 19);
		}
		SECTION("+=")
		{
			CMyString str1("I love");
			CMyString str2(" OOP");
			str1 += str2;
			CompareStringsContents(str1, "I love OOP", 10);
			string str4 = " and programming!";
			str1 += str4;
			CompareStringsContents(str1, "I love OOP and programming!", 27);
		}
		SECTION("==")
		{
			CMyString str1("My string");
			CMyString str2("My string");
			CompareStringsContents(str1, str2.GetStringData(), 9);
			str1 = "";
			str2 = "";
			CompareStringsContents(str1, str2.GetStringData(), 0);
		}
		SECTION("!=")
		{
			CMyString str1("My string");
			CMyString str2("My strings");
			REQUIRE(str1 != str2);
			CompareNotIdenticalStrings(str1, str2.GetStringData(), 10);
		}
		SECTION("[]")
		{
			CMyString str("string");
			str[0] = 'a';
			REQUIRE(str[0] == 'a');
			str[4] = 'k';
			REQUIRE(str[4] == 'k');
			CompareNotIdenticalStrings(str, "atrkng", 6);
		}
		SECTION("<")
		{
			CMyString str1("abcd");
			CMyString str2("abcda");
			REQUIRE(str1 < str2);
			str2 = "abd";
			REQUIRE(str2 < str1);
			REQUIRE_FALSE(str1 < str2);
		}
		SECTION(">=")
		{
			CMyString str1("abcd");
			CMyString str2("abcda");
			REQUIRE(str2 >= str1);
			str2 = "abcd";
			REQUIRE(str2 >= str1);
		}
		SECTION(">")
		{
			CMyString str1("abcd");
			CMyString str2("abcda");
			REQUIRE(str2 > str1);
			str2 = "abcd";
			REQUIRE_FALSE(str2 > str1);
		}
		SECTION("<=")
		{
			CMyString str1("abcd");
			CMyString str2("abcda");
			REQUIRE(str1 <= str2);
			str2 = "abcd";
			REQUIRE(str2 <= str1);
		}
		SECTION(">>")
		{
			std::stringstream strm("string");
			CMyString str;
			strm >> str;
			CompareStringsContents(str, "string", 6);
		}
		SECTION("<<")
		{
			std::stringstream strm;
			CMyString str("string");
			strm << str;
			REQUIRE(strm.str() == "string");
		}
	}

	SECTION("Exceptions")
	{
		SECTION("When we try to get substring of out of range string positions")
		{
			CMyString str("My string!");
			REQUIRE_THROWS_AS(str.SubString(-5, 1), std::out_of_range);
			REQUIRE_THROWS_AS(str.SubString(-5, 10), std::out_of_range);
			REQUIRE_THROWS_AS(str.SubString(20, 1), std::out_of_range);
			REQUIRE_THROWS_AS(str.SubString(0, 11), std::out_of_range);
			REQUIRE_THROWS_AS(str.SubString(10, 2), std::out_of_range);
		}
		SECTION("[] out of range of string")
		{
			CMyString str("string");
			REQUIRE_THROWS_AS(str[-1] = 'a', std::out_of_range);
			REQUIRE_THROWS_AS(str[100] = 'a', std::out_of_range);
		}
	}
}
