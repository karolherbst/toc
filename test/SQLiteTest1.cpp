#define BOOST_TEST_MODULE SQLiteTest
#include <boost/test/unit_test.hpp>

#include "SQLiteQueryBuilder.h"

#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBMS.h>
#include <toc/tocdb/DBResource.h>

using namespace TOC::DB;
#define BOOST_TEST_LOG_LEVEL all

BOOST_AUTO_TEST_CASE( CheckConnection )
{
    // set our driver
    DBResource::Instance().preferedDriver(DBMS::SQLite);
    DBImpl& db = DB::Instance();
    db.setDatabaseName("toc_test_case");

	try
	{
		SQLiteQueryBuilder qb1;
		qb1.entityclass("test");
		db.createTransaction();
		db.executeQuery(qb1.buildDeleteEntityClassQuery(true));
		db.executeQuery(qb1.buildCreateEntityClassQuery());
		db.commit();
	}
	catch (DBException &e){}
}

BOOST_AUTO_TEST_CASE( QueryBuilder )
{
	DBImpl& db = DB::Instance();
	
}
