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
		BOOST_CHECK_EQUAL(FindWordInDictionary("mother", dictionary), "мама ");
	}

	BOOST_AUTO_TEST_CASE(check_a_word_that_is_not_in_the_dictionary)
	{
		Dictionary dictionary;
		dictionary.emplace("мама", "mother");
		dictionary.emplace("mother", "мама");
		FindWordInDictionary("кошка", dictionary);
		BOOST_CHECK_EQUAL(FindWordInDictionary("кошка", dictionary), "");
	}

	BOOST_AUTO_TEST_CASE(translate_a_phrase)
	{
		Dictionary dictionary;
		dictionary.emplace("the red square", "красная площадь");
		dictionary.emplace("красная площадь", "the red square");
		FindWordInDictionary("красная площадь", dictionary);
		BOOST_CHECK_EQUAL(FindWordInDictionary("красная площадь", dictionary), "the red square ");
	}

	BOOST_AUTO_TEST_CASE(translate_a_word_with_several_translations)
	{
		Dictionary dictionary;
		dictionary.emplace("car", "машина");
		dictionary.emplace("car", "автомобиль");
		FindWordInDictionary("car", dictionary);
		BOOST_CHECK_EQUAL(FindWordInDictionary("car", dictionary), "машина автомобиль ");
	}

	BOOST_AUTO_TEST_CASE(check_the_insensitivity_of_the_translator_to_the_register)
	{
		Dictionary dictionary;
		dictionary.emplace("мама", "mother");
		dictionary.emplace("mother", "мама");
		bool isNewWord = false;
		ReadWordAndProcess(dictionary, isNewWord);
		FindWordInDictionary("mother", dictionary);
		BOOST_CHECK_EQUAL(FindWordInDictionary("mother", dictionary), "мама ");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IsNewWordSaved_function)
	BOOST_AUTO_TEST_CASE(ignores_a_new_word_if_the_user_has_not_entered_a_translation)
	{
		Dictionary dictionary;
		dictionary.emplace("мама", "mother");
		const string word = "слово";
		BOOST_CHECK(!SaveNewWord(word, dictionary));
	}
BOOST_AUTO_TEST_SUITE_END()
