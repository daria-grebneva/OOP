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

void CompareStringContents(const CMyString& str1, const char* str2, size_t strSize)
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

void DefaultConstructor(size_t length, const char* inputStr)
{
	CMyString str;
	REQUIRE(str.GetLength() == length);
	CompareStringContents(str, inputStr, length);
}

void SymbolsArrayConstructor(size_t length, const char* inputStr)
{
	CMyString str(inputStr);
	REQUIRE(str.GetLength() == length);
	CompareStringContents(str, inputStr, length);
}

void SymbolsArrayAndLengthConstructor(size_t length, const char* inputStr)
{
	CMyString str(inputStr, length);
	REQUIRE(str.GetLength() == length);
	CompareStringContents(str, inputStr, length);
}

void StlConstructor(const char* inputStr)
{
	string str = inputStr;
	CMyString str1(str);
	REQUIRE(str1.GetLength() == str.size());
}

void CopyConstructor(const char* inputStr)
{
	CMyString str1(inputStr);
	CMyString str2(str1);
	REQUIRE(str1.GetLength() == str2.GetLength());
	CompareStringContents(str2, str1.GetStringData(), str1.GetLength());
}

void MoveConstructor(size_t length, const char* inputStr)
{
	CMyString str(inputStr);
	CMyString str1(std::move(str));
	CompareStringContents(str1, inputStr, length);
	CompareStringContents(str, "", 0);
}

TEST_CASE(" ", "[My String]")
{

	SECTION("Create a normal string")
	{
		SECTION("By default constructor")
		{
			DefaultConstructor(0, "");
		}
		SECTION("By symbols array and by string and length constructors")
		{
			SymbolsArrayConstructor(0, "");
			SymbolsArrayAndLengthConstructor(0, "");
		}

		SECTION("By string")
		{
			SymbolsArrayConstructor(14, "Normal string!");
		}
		SECTION("By stl")
		{
			StlConstructor("Normal string!");
		}
		SECTION("By copy")
		{
			CopyConstructor("Normal string!");
		}
		SECTION("By move")
		{
			MoveConstructor(14, "Normal string!");
		}
	}
	SECTION("Check zero symbol by the constructor without length and with")
	{
		CMyString str("Hell\0o");
		CompareStringContents(str, "Hell", 3);
		CMyString str1("Hell\0o", 4);
		CompareStringContents(str1, "Hell\0o", 4);
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
		CompareStringContents(str, "My string!", 10);
		str.Clear();
		CompareStringContents(str, "", 0);
	}

	SECTION("Check operators")
	{
		SECTION("=")
		{
			CMyString str("My string!");
			str = str;
			CompareStringContents(str, "My string!", 10);
			CMyString str2("Other string");
			str = str2;
			CompareStringContents(str, "Other string", 12);
		}

		SECTION("+")
		{
			SECTION("three instances of class CMyString")
			{
				CMyString str1("I love");
				CMyString str2(" OOP");
				CMyString str3("!");
				CMyString str = str1 + str2 + str3;
				CompareStringContents(str, "I love OOP!", 11);
				string str4 = " programming!";
				CMyString str5 = str1 + str4;
				CompareStringContents(str5, "I love programming!", 19);
			}
			SECTION("instance of class CMyString and class std::string")
			{
				CMyString string1("I love ");
				std::string string2("programming ");
				CMyString str1 = string1 + string2;
				CMyString str2 = string2 + string1;
				CompareStringContents(str1, "I love programming ", 13);
				CompareStringContents(str2, "programming I love ", 13);
			}
			SECTION("instance of class CMyString and const char*")
			{
				const char* string2 = "programming ";
				CMyString string1("I love ");
				CMyString str1 = string1 + string2;
				CMyString str2 = string2 + string1;
				CompareStringContents(str1, "I love programming ", 13);
				CompareStringContents(str2, "programming I love ", 13);
			}
		}
		SECTION("+=")
		{
			CMyString str1("I love");
			CMyString str2(" OOP");
			str1 += str2;
			CompareStringContents(str1, "I love OOP", 10);
			string str4 = " and programming!";
			str1 += str4;
			CompareStringContents(str1, "I love OOP and programming!", 27);
		}
		SECTION("==")
		{
			CMyString str1("My string");
			CMyString str2("My string");
			CompareStringContents(str1, str2.GetStringData(), 9);
			str1 = "";
			str2 = "";
			CompareStringContents(str1, str2.GetStringData(), 0);
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
			SECTION("read character in string by index")
			{
				CMyString str("string");
				const auto ch1 = str[0];
				REQUIRE(ch1 == 's');
				const auto ch2 = str[3];
				REQUIRE(ch2 == 'i');
				const auto ch3 = str[1];
				REQUIRE(ch3 == 't');
			}
			SECTION("write character in string by index")
			{
				CMyString str("string");
				auto ch = 't';
				str[0] = ch;
				REQUIRE(str[0] == 't');
				str[2] = ch;
				REQUIRE(str[2] == 't');
				str[5] = 's';
				REQUIRE(str[5] == 's');
			}
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
			CompareStringContents(str, "string", 6);
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
			SECTION("when we try to write")
			{
				CMyString str("string");
				REQUIRE_THROWS_AS(str[-1] = 'a', std::out_of_range);
				REQUIRE_THROWS_AS(str[100] = 'a', std::out_of_range);
			}
			SECTION("when we try to read")
			{
				CMyString str("string");
				REQUIRE_THROWS_AS(str[-1], std::out_of_range);
				REQUIRE_THROWS_AS(str[100], std::out_of_range);
			}
		}
	}
}
