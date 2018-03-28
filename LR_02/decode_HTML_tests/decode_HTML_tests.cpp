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

	BOOST_AUTO_TEST_CASE(makes_replacement_of_entities)
	{
		string strWithHtmlEntities = "I&apos;d like to &lt;listen&gt; to &apos;music&apos; ";
		string requiredStr = "I'd like to <listen> to 'music' ";
		BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);
	}

BOOST_AUTO_TEST_SUITE_END()
