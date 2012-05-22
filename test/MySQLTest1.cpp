#define BOOST_TEST_MODULE MySQLDriverTest
#include <boost/test/unit_test.hpp>

#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBResource.h>

using namespace TOC::DB;

BOOST_AUTO_TEST_CASE( CheckConnection )
{
	// set our driver
	DBResource::Instance().preferedDriver("MySQL");
	DBImpl& db = DB::Instance();
	db.setDatabaseName("toc_test_case");
	db.setUserName("");

	db.executeQuery(String("SHOW DATABASES;"));
}
