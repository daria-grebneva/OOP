#include "stdafx.h"
#include "..\decode_HTML\decode_HTML.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)

	BOOST_AUTO_TEST_CASE(makes_empty_string_from_empty_string)
	{
		BOOST_CHECK_EQUAL(HtmlDecode(""), "");
	}

	BOOST_AUTO_TEST_SUITE(when_input_string_is_without_html_entities)
		BOOST_AUTO_TEST_CASE(return_source_string)
		{
			string strWithoutHtml = "We don`t: \"have\" HTML special symbols";
			BOOST_CHECK_EQUAL(HtmlDecode(strWithoutHtml), strWithoutHtml);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_input_html_entities_is_incomplete)
		BOOST_AUTO_TEST_CASE(return_source_string)
		{
			string strWithoutHtmlEntities = "It&lts &ltnot&gt &gteasy&quot. C&ampA&apSE";
			BOOST_CHECK_EQUAL(HtmlDecode(strWithoutHtmlEntities), strWithoutHtmlEntities);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_input_string_is_html_entities)
		BOOST_AUTO_TEST_CASE(makes_replacement_of_less_than_entity)
		{
			string strWithHtmlEntities = "1 &lt; 2";
			string requiredStr = "1 < 2";
			BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);
		}
		BOOST_AUTO_TEST_CASE(makes_replacement_of_greater_than_entity)
		{
			string strWithHtmlEntities = "3 &gt; 2";
			string requiredStr = "3 > 2";
			BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);
		}
		BOOST_AUTO_TEST_CASE(makes_replacement_of_apostrophe_entity)
		{
			string strWithHtmlEntities = "I&apos;d like to listen to &apos;music&apos; ";
			string requiredStr = "I'd like to listen to 'music' ";
			BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);
		}
		BOOST_AUTO_TEST_CASE(makes_replacement_of_quote_entity)
		{
			string strWithHtmlEntities = "I would like to listen to &quot;music&quot; ";
			string requiredStr = "I would like to listen to \"music\" ";
			BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);
		}
		BOOST_AUTO_TEST_CASE(makes_replacement_of_ampersand_entity)
		{
			string strWithHtmlEntities = "I would like to listen to music &amp; play footbal ";
			string requiredStr = "I would like to listen to music & play footbal ";
			BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
