#define BOOST_TEST_MODULE ExceptionTest
#include <boost/test/unit_test.hpp>

#include <toc/tocexception.h>

using namespace TOC::core;

COREEXCEPTION_SUBCLASS( TestException, "test test test");
SUBCLASS_OF_COREEXCEPTION_SUBCLASS( TestException, ChildTestException, "test test test");

#define THROW_AND_CATCH_AND_TEST( exception_type )        \
try{throw exception_type();}catch(CoreException &e){      \
BOOST_REQUIRE(e.getMessage().find( "" ) != String::npos); \
BOOST_REQUIRE(e.getMessage() == e.what());}

BOOST_AUTO_TEST_CASE( _CoreException )
{
	THROW_AND_CATCH_AND_TEST( CoreException );
}

BOOST_AUTO_TEST_CASE( DerivedCoreException)
{
	THROW_AND_CATCH_AND_TEST( TestException );
}

BOOST_AUTO_TEST_CASE( DerivedCoreExceptionSubclass)
{
	THROW_AND_CATCH_AND_TEST( ChildTestException );
}
