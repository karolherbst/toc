#define BOOST_TEST_MODULE MySQLDriverTest

#define PREFERED_DRIVER DBMS::MySQL
#define QUERY_BUILDER_CLASS MySQLQueryBuilder
#define ADDITIONAL_AUTH_CALLS \
db.setUserName("toc_test");   \
db.setUserPassword("toc_test");

#include "MySQLQueryBuilder.h"

#include "DBTestTemplate.hpp"
