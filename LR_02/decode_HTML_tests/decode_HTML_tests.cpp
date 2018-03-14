#include "stdafx.h"
#include "..\decode_HTML\decode_HTML.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)

BOOST_AUTO_TEST_CASE(return_empty_string_if_input_are_empty_string)
{
	BOOST_CHECK_EQUAL(HtmlDecode(""), "");
}

//без нужных строк для декодирования 
BOOST_AUTO_TEST_CASE(source_string_without_html)
{
	string strWithoutHtml = "We don`t: \"have\" HTML special symbols";
	BOOST_CHECK_EQUAL(HtmlDecode(strWithoutHtml), strWithoutHtml);
}

//неполные строки 
BOOST_AUTO_TEST_CASE(entities_not_string)
{
	string strWithoutHtmlEntities = "It&lts &ltnot&gt &gteasy&quot. C&ampA&apSE";
	BOOST_CHECK_EQUAL(HtmlDecode(strWithoutHtmlEntities), strWithoutHtmlEntities);
}

BOOST_AUTO_TEST_CASE(replace_entities)
{
	string strWithHtmlEntities = "I&apos;d like to &lt;listen&gt; to &apos;music&apos; ";
	string requiredStr = "I'd like to <listen> to 'music' ";
	BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);

	strWithHtmlEntities = "We&quot; went&apos;&apos;&apos; the champion&apos;s.";
	requiredStr = "We\" went''' the champion's.";
	BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);
}

BOOST_AUTO_TEST_SUITE_END()