#include "stdafx.h"
#include "../URL_parser/URL_parser.h"

TEST_CASE("TrimBlanks test")
{
	CHECK(TrimBlanks("") == "");
	CHECK(TrimBlanks("Hello") == "Hello");
	CHECK(TrimBlanks("   Hello") == "Hello");
	CHECK(TrimBlanks("Hello   ") == "Hello");
	CHECK(TrimBlanks("    Hello   ") == "Hello");
	CHECK(TrimBlanks("    ") == "");
	CHECK(TrimBlanks("A") == "A");
}
