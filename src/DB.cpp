/*
*  Copyright (c) by Karol Herbst <projects@karolherbst.de>
*
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*
*/

/*
 * TODO
 * executeBoolQuery
 */

#include <toc/tocdb/DB.h>

#include <toc/boost/extension/shared_library.hpp>
#include <boost/thread/thread.hpp>

#include <toc/tocdb/DBDriver.h>
#include <toc/tocdb/DBExceptions.h>
#include <toc/tocdb/DBTable.h>

namespace TOC
{
	using core::CoreException;
	namespace DB
	{
		const static std::string DB_CONNECT_FAILED = "Connection to Database failed! Reason: %r%";
		const static std::string DB_CONNECT_SUCCESS = "Connected to Database!";
		const static std::string DB_FATAL_ERROR = "Database failure, we are stopping here";
		const static std::string QUERY_EXECUTE_FAILED = "Failed to execute query: %query%";
		
		DBImpl::
		DBImpl()
		:	driver(NULL){}
		
		DBImpl::
		~DBImpl()
		{
			close();
			delete driver.get();
		}
		
		void
		DBImpl::
		initDriver()
		{
			driver.reset(DBResource::Instance().newDriver());
			driver->databaseName(db);
			driver->userName(user);
			driver->userPassword(pw);
			driver->serverURL(url);
			driver->serverPort(port);
			Open();
		}
		
		void
		DBImpl::
		setConnectionInfo(std::string& server,
		                  uint32_t port,
		                  std::string& user,
		                  std::string& pw,
		                  std::string& db)
		{
			setServerURL(server);
			setServerPort(port);
			setUserName(user);
			setUserPassword(pw);
			setDatabaseName(db);
		}
		
		void
		DBImpl::
		setServerPort(uint32_t _port)
		{
			port = _port;
		}
		
		void
		DBImpl::
		Open()
		{
			try
			{
				driver->auth();
			}
			catch (DBException& e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
				throw AuthenticationFailedException();
			}
			logger.log<LOGGINGTYPE::INFO>(DB_CONNECT_SUCCESS + " tid:");
		}
		
		void
		DBImpl::
		close()
		{
			// todo: close in each thread

			// if no driver loaded, why we have to close connection?
			if (driver.get() == NULL)
				return;
			driver->close();
			logger.log<LOGGINGTYPE::INFO>("Database shut down");
		}
		
		DBTable
		DBImpl::
		operator[](const std::string& str)
		{
			if (driver.get() == NULL)
				initDriver();
			return DBTable(str);
		}
		
		void
		DBImpl::
		createTransaction()
		{
			if (driver.get() == NULL)
				initDriver();
			try
			{
				driver->startTransaction();
			}
			catch (DBException &e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
			}
		}
		
		void
		DBImpl::
		commit()
		{
			if (driver.get() == NULL)
				initDriver();
			try
			{
				driver->commit();
			}
			catch (DBException &e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
			}
		}
		
		void
		DBImpl::
		rollback()
		{
			if (driver.get() == NULL)
				initDriver();
			try
			{
				driver->rollback();
			}
			catch (DBException &e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
			}
		}
		
		void
		DBImpl::
		executeQuery(const std::string& q)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
			try
			{
				driver->exec(q);
			}
			catch (DBException &e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
				throw CoreException("a critical error occured during DB::executeQuery");
			}
		}
		
		void
		DBImpl::
		executeBoolQuery(const std::string& q,
		                 bool&)
		{
			logger.log<LOGGINGTYPE::DEBUG>(q);
			throw MethodNotImplementedException();
		}
		
		void
		DBImpl::
		executeSingleValueQuery(const std::string& q,
		                        std::string& result)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
			try
			{
				driver->executeSingleValueQuery(q,
				                                result);
			}
			catch (DBException &e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
				throw e;
			}
		}
		
		void
		DBImpl::
		executeSingleRowQuery(const std::string& q,
		                      std::map<std::string,
		                               std::string>& result)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
			try
			{
				driver->executeSingleRowQuery(q,
				                              result);
			}
			catch (DBException &e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
				throw e;
			}
		}
		
		void
		DBImpl::
		executeSingleColQuery(const std::string& q,
		                      std::vector<std::string>& result)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
			try
			{
				driver->executeSingleColQuery(q,
				                              result);
			}
			catch (DBException &e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
				throw e;
			}
		}
		
		void
		DBImpl::
		executeMultiRowQuery(const std::string& q,
		                     std::vector<std::map<std::string,
		                                          std::string>>&)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
			throw MethodNotImplementedException();
		}
	}
}
