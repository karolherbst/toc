#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <toc/toclogger/DefaultLogger.h>

using namespace TOC;

BOOST_AUTO_TEST_CASE( LOGGERTest )
{
    DefaultLogger logger(true, true, true, true);
    for(long i = 0; i < 8; i++)
    {
        logger.log<ERROR>("hello");
    }
    std::cerr << "finished" << std::endl;
}
