/*
 TODO:
 we should use the official MySQL C library, cause we do the same, as a c++
 MySQL wrapping library but with a very lowelevel data access.
 Maybey we'll can use the official C++ library if it's integrate easier in
 our architecture.
 
 TODO2:
 how should we build querys?
 I think a SQLQuerybuilder class should be fully acceptable
 
 template <int16_t type> // SQL, BSON, etc...
 class Querybuild.
 */

#include "MySQLDriver.h"
#include "MySQLQueryBuilder.h"
#include <boost/foreach.hpp>
#include <toc/tocdb/DBExceptions.h>

namespace TOC
{
    using core::CoreException;
    namespace DB
    {
        MySQLDriver::MySQLDriver()
        :   conn(new mysqlpp::Connection(true))
        {
            
        }
        
        MySQLDriver::
        ~MySQLDriver()
        {
            delete conn;
        }
        
        void
        MySQLDriver::
        close()
        {
            conn->disconnect();
        }
        
        bool
        MySQLDriver::
        auth()
        {
            try
            {
                return conn->connect(databaseName().c_str(),
                                     serverURL().c_str(),
                                     userName().c_str(),
                                     userPassword().c_str(),
                                     serverPort());
            }
            catch (mysqlpp::ConnectionFailed& e)
            {
                throw CoreException(e.what());
            }
            catch (mysqlpp::DBSelectionFailed& e)
            {
                throw CoreException(e.what());
            }
        }
        
        void
        MySQLDriver::
        startTransaction()
        {
            exec(MySQLQueryBuilder::StartTransaction());
        }
        
        void
        MySQLDriver::
        commit()
        {
            exec(MySQLQueryBuilder::CommitTransaction());
        }
        
        void
        MySQLDriver::
        rollback()
        {
            exec(MySQLQueryBuilder::RollbackTransaction());
        }
        
        bool
        MySQLDriver::
        exec(const String& q)
        {
            try
            {
                mysqlpp::Query myquery(conn);
                return myquery.exec(q);
            }
            catch (mysqlpp::BadQuery& e)
            {
                handleMYSQLerrno(e.errnum(),
                                 e.what());
                return false;
            }
            catch (mysqlpp::Exception& e)
            {
                throw CoreException("undefined DB failure!");
            }
        }
        
        mysqlpp::SimpleResult
        MySQLDriver::
        execute(const String& q)
        {
            try
            {
                mysqlpp::Query myquery(conn);
                return myquery.execute(q);
            }
            catch
            (mysqlpp::BadQuery& e)
            {
                handleMYSQLerrno(e.errnum(),
                                 e.what());
                return mysqlpp::SimpleResult();
            }
            catch (mysqlpp::Exception& e)
            {
                throw CoreException("undefined DB failure!");
            }
        }
        
        mysqlpp::StoreQueryResult
        MySQLDriver::
        store(const String& q)
        {
            try
            {
                mysqlpp::Query myquery(conn);
                mysqlpp::StoreQueryResult result = myquery.store(q);
                
                if (result.size() != 0)
                    return result;
                else throw DB::EmptyResultException();
            }
            catch (mysqlpp::BadQuery& e)
            {
                handleMYSQLerrno(e.errnum(),
                                 e.what());
                return mysqlpp::StoreQueryResult();
            }
            catch (mysqlpp::Exception& e)
            {
                throw CoreException("undefined DB failure!");
            }
        }
        
        DB::DBSingleValueResult
        MySQLDriver::
        executeSingleValueQuery(const String& query,
                                String& resultHolder)
        {
            store(query)[0][0].to_string(resultHolder);
            return DB::DBSingleValueResult(resultHolder);
        }
        
        DB::DBSingleColResult
        MySQLDriver::
        executeSingleColQuery(const String& q,
                              std::vector<String>& resultHolder)
        {
            BOOST_FOREACH(const mysqlpp::Row& row,
                          store(q))
            {
                resultHolder.push_back(row[0].c_str());
            }
            
            return DB::DBSingleColResult(resultHolder);
        }
        
        void
        MySQLDriver::
        handleMYSQLerrno(int32_t error,
                         const char* message)
        {
            logger.log<LOGGINGTYPE::ERROR>(message);
            switch (error)
            {
                case 1146:
                    throw DB::TableDoesntExistException(message);
                    break;
                default:
                    throw DB::DBException(message);
                    break;
            }
        }

		DBDriver*
		MySQLDriver::
		newDriver()
		{
			return new MySQLDriver();
		}
    }
}