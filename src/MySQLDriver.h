#include <boost/noncopyable.hpp>
#include <mysql++/mysql++.h>
#include <toc/tocdb/DBDriver.h>
#include <toc/toclogger.h>
#include <toc/tocstring/TocString.h>

CREATE_LOGGER_NAME_CLASS_DEF(MySQLLog);

namespace TOC
{
    namespace DB
    {
        class MySQLDriver : public DBDriver, boost::noncopyable
        {
        public:
            MySQLDriver();
            ~MySQLDriver();
            
            void close();
            /*
             * return true if auth was successfull
             * return false if connected without authentication
             * throws CoreException if authentication fails
             */
            bool auth();
            
            void startTransaction();
            void commit();
            void rollback();
            bool exec(const String&);
            DBSingleValueResult executeSingleValueQuery(const String& query,
                                                        String& resultHolder);
            DBSingleColResult executeSingleColQuery(const String& q,
                                                    std::vector<String>& result);
            
            // not in interface:
            void handleMYSQLerrno(int32_t,
                                  const char* message);
            
			static DBDriver* newDriver();
        private:
            mysqlpp::Connection* conn;
            
            mysqlpp::SimpleResult execute(const String&);
            mysqlpp::StoreQueryResult store(const String&);
            
			CREATE_LOGGER(logger, MySQLLog);
        };
    }
}
