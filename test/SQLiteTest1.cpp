#define BOOST_TEST_MODULE SQLiteTest
#include <boost/test/unit_test.hpp>

#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBResource.h>

using namespace TOC::DB;
#define BOOST_TEST_LOG_LEVEL all

BOOST_AUTO_TEST_CASE( CheckConnection )
{
	BOOST_TEST_MESSAGE("hi");
    // set our driver
    DBResource::Instance().preferedDriver("SQLite");
    DBImpl& db = DB::Instance();
    db.setDatabaseName("toc_test_case");

	try
	{
		db.executeQuery(String("CREATE TABLE bla (ID INT U;NSIGNED NOT NULL)"));
	}
	catch (MalformedQueryException &e){}
}
