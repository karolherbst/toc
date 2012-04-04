#define BOOST_TEST_MAIN 1
#include <boost/test/unit_test.hpp>

#include <toc/toccore/Version.h>

BOOST_AUTO_TEST_CASE( VersionTest )
{
    using TOC::core::Version;
    
    Version v1111(1,1,1,1);
    Version v1111_2(1,1,1,1);
    Version v1112(1,1,1,2);
    Version v1122(1,1,2,2);
    Version v1222(1,2,2,2);
    Version v2222(2,2,2,2);
    
    BOOST_REQUIRE(v1111 < v1112);
    BOOST_REQUIRE(v1111 < v1122);
    BOOST_REQUIRE(v1111 < v1222);
    BOOST_REQUIRE(v1111 < v2222);
    BOOST_REQUIRE(v1111 == v1111_2);
    
    BOOST_CHECK(v1112 > v1111);
    BOOST_CHECK(v1122 > v1111);
    BOOST_CHECK(v1222 > v1111);
    BOOST_CHECK(v2222 > v1111);
    
    BOOST_CHECK(v1111 != v2222);
}
