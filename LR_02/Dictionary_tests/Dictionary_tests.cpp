#include "stdafx.h"
#include "..\Dictionary\Dictionary.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(FindWordInDictionary_function)

	BOOST_AUTO_TEST_CASE(find_word_in_dictionary_and_show_translation)
	{
		Dictionary dictionary;
		dictionary.emplace("мама", "mother");
		dictionary.emplace("mother", "мама");
		FindWordInDictionary("mother", dictionary);
		BOOST_CHECK_EQUAL(FindWordInDictionary("mother", dictionary), "мама");
	}
	BOOST_AUTO_TEST_CASE(check_a_word_that_is_not_in_the_dictionary)
	{
		Dictionary dictionary;
		dictionary.emplace("мама", "mother");
		dictionary.emplace("mother", "мама");
		FindWordInDictionary("кошка", dictionary);
		BOOST_CHECK_EQUAL(FindWordInDictionary("кошка", dictionary), "");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IsNewWordSaved_function)
	BOOST_AUTO_TEST_CASE(ignores_a_new_word_if_the_user_has_not_entered_a_translation)
	{
		Dictionary dictionary;
		dictionary.insert(make_pair("мама", "mother"));
		const string word = "слово";
		BOOST_CHECK(!SaveNewWord(word, dictionary));
	}
BOOST_AUTO_TEST_SUITE_END()
