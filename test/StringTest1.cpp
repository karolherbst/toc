#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <toc/tocstring.h>

#define TESTSTRING "Hallo, Welt"
const char testString[] = TESTSTRING;
#define TESTCOMMAND "/hey wouho \"you are evil!\" now!"
const char testCommand[] = TESTCOMMAND;

// BOOST_CHECK
// BOOST_CHECK_EQUAL
// BOOST_REQUIRE
// BOOST_ERROR
// BOOST_FAIL

BOOST_AUTO_TEST_CASE( STRINGGetStringUntilChar )
{
    // constructors
    const std::string testCommandString(testCommand);
    BOOST_REQUIRE_EQUAL(getStringUntilChar(testCommandString,
                                           ' '), "/hey");
}

BOOST_AUTO_TEST_CASE( STRINGGetStringAfterChar )
{
    const std::string testCommandString(testCommand);
    BOOST_REQUIRE_EQUAL(getStringAfterChar(testCommandString,
                                           'y'), " wouho \"you are evil!\" now!");
}

BOOST_AUTO_TEST_CASE( STRINGGetArguments )
{
    const std::string testCommandString(testCommand);
    std::vector<std::string> args;
    
    storeArgumentsIn(testCommandString,
                     args);
    
    BOOST_REQUIRE_EQUAL(args.size(), 4);
    BOOST_REQUIRE_EQUAL(args[0], "/hey");
    BOOST_REQUIRE_EQUAL(args[1], "wouho");
    BOOST_REQUIRE_EQUAL(args[2], "you are evil!");
    BOOST_REQUIRE_EQUAL(args[3], "now!");
}
