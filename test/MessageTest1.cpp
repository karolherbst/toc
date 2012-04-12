#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <toc/tocmessage.h>
#include <toc/tocstring/TocString.h>

using TOC::message::ChatMessage;

BOOST_AUTO_TEST_CASE( test1 )
{
	const String testMessage = CSTRING("hallo");
	ChatMessage cm1(testMessage);
	
	// simulate sending
	const Char* data = cm1.data();
	ChatMessage cm2(data);
	
//	BOOST_REQUIRE_EQUAL(cm2.body(), cm1.body());
//	BOOST_REQUIRE_EQUAL(cm2.body(), testMessage);
}
