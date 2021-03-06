#include <boost/test/unit_test.hpp>

#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBMS.h>
#include <toc/tocdb/DBResource.h>
#include <toc/tocdb/StandardTypes.h>

using namespace TOC::DB;

BOOST_AUTO_TEST_CASE( CheckConnection )
{
    // set our driver
    DBResource::Instance().preferedDriver(PREFERED_DRIVER);
    DBImpl& db = DB::Instance();
    db.setDatabaseName("toc_test_case");
#ifdef ADDITIONAL_AUTH_CALLS
	ADDITIONAL_AUTH_CALLS
#endif
	db.initDriver();
}

BOOST_AUTO_TEST_CASE( QueryBuilder )
{
	DBImpl& db = DB::Instance();

	try
	{
		QUERY_BUILDER_CLASS qb;
		qb.entityclass("test");
		db.createTransaction();
		db.executeQuery(qb.buildDeleteEntityClassQuery(true));
		db.executeQuery(qb.buildCreateEntityClassQuery());

		// build a table
		qb.attribute("name");
		db.executeQuery(qb.buildAddAttributeQuery(std::string("karol"), TOC::DBString, 32));
		qb.attribute("age");
		db.executeQuery(qb.buildAddAttributeQuery(std::string("0"), TOC::DBInt, 10));
		qb.attribute("gender");
		db.executeQuery(qb.buildAddAttributeQuery(std::string("M"), TOC::DBString, 1));

		// create a row
		std::map<std::string, std::string> values;
		values["ID"] = "1";
		values["name"] = "herbst";
		values["age"] = "21";
		values["gender"] = "M";
		// it have to possible to execute this query both;
		db.executeQuery(qb.buildIdInsertQuery(values));
		db.executeQuery(qb.buildIdInsertQuery(values));

		qb.attribute("age");
		qb.id(1);
		db.executeQuery(qb.buildSingleValueInsertQuery("22"));
		db.commit();

		// now we want to check some values stored in the database;
		std::map<std::string, std::string> result;
		qb.entityclass("test");
		qb.attribute("");
		qb.id(1);
		db.executeSingleRowQuery(qb.buildSingleRowSelectQuery() , result);
		BOOST_REQUIRE_EQUAL(result.at("ID"), "1");
		BOOST_REQUIRE_EQUAL(result.at("name"), "herbst");
		BOOST_REQUIRE_EQUAL(result.at("age"), "22");
		BOOST_REQUIRE_EQUAL(result.at("gender"), "M");

		// insert a single values
		db.createTransaction();
		qb.entityclass("test");
		qb.attribute("name");
		qb.id(2);
		db.executeQuery(qb.buildSingleValueInsertQuery("name1"));
		db.commit();

		std::map<std::string, std::string> result2;
		db.executeSingleRowQuery(qb.buildSingleRowSelectQuery(), result2);
		BOOST_REQUIRE_EQUAL(result2.at("name"), "name1");

		// search for a specific data type with logical primary key
		qb.entityclass("test");
		qb.addWherePair("name", "herbst");
		std::string result3;
		db.executeSingleValueQuery(qb.buildIDSelectQuery(), result3);
		BOOST_REQUIRE_EQUAL(result3, "1");
	}
	catch (DBException &e){}
}
