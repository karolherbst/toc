#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <toc/tocstring.h>

BOOST_AUTO_TEST_CASE( STRINGGetStringUntilChar )
{
    const String testCommandString(CSTRING("/hey wouho \"you are evil!\" now!"));
//    BOOST_REQUIRE_EQUAL(getStringUntilChar(testCommandString,
//                                           CCHAR(' ')), CSTRING("/hey"));
}

BOOST_AUTO_TEST_CASE( STRINGGetStringAfterChar )
{
    const String testCommandString(CSTRING("/hey wouho \"you are evil!\" now!"));
//    BOOST_REQUIRE_EQUAL(getStringAfterChar(testCommandString,
//                                           CCHAR('y')), CSTRING(" wouho \"you are evil!\" now!"));
}

BOOST_AUTO_TEST_CASE( STRINGGetArguments )
{
    const String testCommandString(CSTRING("/hey wouho \"you are evil!\" now!"));
    std::vector<String> args;

    storeArgumentsIn(testCommandString,
                     args);

//    BOOST_REQUIRE_EQUAL(args.size(), 4);
//    BOOST_REQUIRE_EQUAL(args[0], CSTRING("/hey"));
//    BOOST_REQUIRE_EQUAL(args[1], CSTRING("wouho"));
//    BOOST_REQUIRE_EQUAL(args[2], CSTRING("you are evil!"));
//    BOOST_REQUIRE_EQUAL(args[3], CSTRING("now!"));
}
