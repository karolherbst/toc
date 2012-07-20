#define BOOST_TEST_MODULE SQLiteTest

#define PREFERED_DRIVER DBMS::SQLite
#define QUERY_BUILDER_CLASS SQLiteQueryBuilder

#include "SQLiteQueryBuilder.h"

#include "DBTestTemplate.tpp"
