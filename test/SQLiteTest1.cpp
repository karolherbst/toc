#define BOOST_TEST_MODULE SQLiteTest
#include <boost/test/unit_test.hpp>

#include "SQLiteQueryBuilder.h"

#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBMS.h>
#include <toc/tocdb/DBResource.h>
#include <toc/tocdb/StandardTypes.h>

using namespace TOC::DB;

BOOST_AUTO_TEST_CASE( CheckConnection )
{
    // set our driver
    DBResource::Instance().preferedDriver(DBMS::SQLite);
    DBImpl& db = DB::Instance();
    db.setDatabaseName("toc_test_case");
	db.initDriver();
}

BOOST_AUTO_TEST_CASE( QueryBuilder )
{
	DBImpl& db = DB::Instance();

	try
	{
		SQLiteQueryBuilder qb;
		qb.entityclass("test");
		db.createTransaction();
		db.executeQuery(qb.buildDeleteEntityClassQuery(true));
		db.executeQuery(qb.buildCreateEntityClassQuery());

		// build a table
		qb.attribute("name");
		db.executeQuery(qb.buildAddAttributeQuery(String("karol"), TOC::DBString, 32));
		qb.attribute("age");
		db.executeQuery(qb.buildAddAttributeQuery(String("0"), TOC::DBInt, 10));
		qb.attribute("gender");
		db.executeQuery(qb.buildAddAttributeQuery(String("M"), TOC::DBString, 1));

		// create a row
		std::map<String, String> values;
		values["ID"] = "1";
		values["name"] = "herbst";
		values["age"] = "21";
		values["gender"] = "M";
		// it have to possible to execute this query both;
		db.executeQuery(qb.buildIdInsertQuery(values));
		db.executeQuery(qb.buildIdInsertQuery(values));

		db.commit();
	}
	catch (DBException &e){}
}
