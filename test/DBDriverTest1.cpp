#define BOOST_TEST_MODULE DBDriverTest
#include <boost/test/unit_test.hpp>

#include <toc/tocdb/DBResource.h>
#include <toc/tocstring.h>

#define DBResource TOC::DB::DBResource::Instance()

using TOC::DB::AbstractQueryBuilder;
using TOC::DB::DBDriver;

static bool skip = false;
static std::string notLoadedDriver = "sdakdjld3aijld";

BOOST_AUTO_TEST_CASE( CreateBuiltInDrivers )
{
	std::list<std::string> drivers = DBResource.availableDrivers();
	if ( drivers.size() == 0 ) {
		std::cout << "No built-in drivers found. No Driver testing!" << std::endl;
	}
	else
	{
		// check only the first driver
		// we will test speficic drivers in different tests
		DBResource.preferedDriver(*drivers.begin());
		DBDriver* d = DBResource.newDriver();
		AbstractQueryBuilder* q = DBResource.newQueryBuilder();

		// delete pointers
		delete d;
		delete q;
	}
}

BOOST_AUTO_TEST_CASE( DBResource__registerDriver )
{
	try
	{
		DBResource.registerDriver("stupidDriver",
		                          "/damn");
		BOOST_FAIL("TOC::DB::DBResource should not load not existing libs");
	}
	catch (TOC::DB::DriverLibNotValid &){}

	try
	{
		DBResource.registerDriver("stupidDriver",
	 	                          "/lib/libpthread.so.0");
		BOOST_FAIL("No, libpthread is not valid!");
	}
	catch (TOC::DB::DriverLibNotValid &){}
}

BOOST_AUTO_TEST_CASE( DBResource__isLoaded )
{
	BOOST_REQUIRE( !DBResource.isLoaded(notLoadedDriver) );
}

BOOST_AUTO_TEST_CASE( DBResource__DriverEntry__isBuiltIn )
{
	// a not loaded driver is not built in at all
	BOOST_REQUIRE( !DBResource.isBuiltIn(notLoadedDriver) );
}

BOOST_AUTO_TEST_CASE( DBResource__preferedDriver )
{
	try
	{
		DBResource.preferedDriver(notLoadedDriver);
		BOOST_FAIL("DBResource should not set a not loaded driver as prefered!");
	}
	catch(TOC::DB::DriverNotLoaded &){}
}
