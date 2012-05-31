#define BOOST_TEST_MODULE MySQLDriverTest
#include <boost/test/unit_test.hpp>

#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBMS.h>
#include <toc/tocdb/DBResource.h>

#include "MySQLQueryBuilder.h"

using namespace TOC::DB;

BOOST_AUTO_TEST_CASE( CheckConnection )
{
	// set our driver
	DBResource::Instance().preferedDriver(DBMS::MySQL);
	DBImpl& db = DB::Instance();
	db.setDatabaseName("toc_test_case");
	db.setUserName("toc_test");
	db.setUserPassword("toc_test");
	db.initDriver();
}

BOOST_AUTO_TEST_CASE( QBCreateEntityclass )
{
	DBImpl& db = DB::Instance();
	MySQLQueryBuilder qb1;

	qb1.entityclass("test");
	db.executeQuery(qb1.buildDeleteEntityClassQuery(true));
	db.executeQuery(qb1.buildCreateEntityClassQuery());
}
