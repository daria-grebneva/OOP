#include "stdafx.h"
#include "..\Dictionary\Dictionary.h"

BOOST_AUTO_TEST_SUITE(FindWordInDictionary_function)
	BOOST_AUTO_TEST_CASE(find_word_in_dictionary_and_show_translation)
	{
		MMAP_STRING_STRING dictionary;
		dictionary.insert(make_pair("мама", "mother"));
		FindWordInDictionary("mother", dictionary);
		BOOST_CHECK_EQUAL(FindWordInDictionary("mother", dictionary), "мама");
	}
	BOOST_AUTO_TEST_CASE(check_a_word_that_is_not_in_the_dictionary)
	{
		MMAP_STRING_STRING dictionary;
		dictionary.insert(make_pair("мама", "mother"));
		FindWordInDictionary("кошка", dictionary);
		BOOST_CHECK_EQUAL(FindWordInDictionary("кошка", dictionary), "");
	}
BOOST_AUTO_TEST_SUITE_END()
