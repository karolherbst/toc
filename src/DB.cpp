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
#include <toc/tocdb/DBResult.h>
#include <toc/tocdb/DBTable.h>

namespace TOC
{
	using core::CoreException;
	namespace DB
	{
		const static String DB_CONNECT_FAILED		= CSTRING("Connection to Database failed! Reason: %r%");
		const static String DB_CONNECT_SUCCESS		= CSTRING("Connected to Database!");
		const static String DB_FATAL_ERROR		= CSTRING("Database failure, we are stopping here");
		const static String QUERY_EXECUTE_FAILED	= CSTRING("Failed to execute query: %query%");
		
		DBImpl::
		DBImpl()
		:   driver(NULL)
		{}
		
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
			driver->databaseName() = db;
			driver->userName() = user;
			driver->userPassword() = pw;
			driver->serverURL() = url;
			driver->serverPort() = port;
			Open();
		}
		
		void
		DBImpl::
		setConnectionInfo(String& server,
		                  uint32_t port,
		                  String& user,
		                  String& pw,
		                  String& db)
		{
			setServerURL(server);
			setServerPort(port);
			setUserName(user);
			setUserPassword(pw);
			setDatabaseName(db);
		}
		
		void
		DBImpl::
		setDatabaseName(String& _db)
		{
			db = _db;
		}
		
		void
		DBImpl::
		setUserName(String& name)
		{
			user = name;
		}
		
		void
		DBImpl::
		setUserPassword(String& _pw)
		{
			pw = _pw;
		}
		
		void
		DBImpl::
		setServerURL(String& _url)
		{
			url = _url;
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
			catch (CoreException& e)
			{
				logger.log<LOGGINGTYPE::ERROR>(e.what());
				throw AuthenticationFailedException();
			}
			logger.log<LOGGINGTYPE::INFO>(DB_CONNECT_SUCCESS + CSTRING(" tid:"));
		}
		
		void
		DBImpl::
		close()
		{
			// todo: close in each thread
			if (driver.get() == NULL)
				initDriver();
			driver->close();
			logger.log<LOGGINGTYPE::INFO>("Database shut down");
		}
		
		DBTable
		DBImpl::
		operator[](const String& str)
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
			driver->startTransaction();
		}
		
		void
		DBImpl::
		commit()
		{
			if (driver.get() == NULL)
				initDriver();
			driver->commit();
		}
		
		void
		DBImpl::
		rollback()
		{
			if (driver.get() == NULL)
				initDriver();
			driver->rollback();
		}
		
		void
		DBImpl::
		executeQuery(const String& q)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
			driver->exec(q);
		}
		
		void
		DBImpl::
		executeBoolQuery(const String& q,
		                 bool&)
		{
			logger.log<LOGGINGTYPE::DEBUG>(q);
		}
		
		void
		DBImpl::
		executeSingleValueQuery(const String& q,
		                        String& result)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
			DBSingleValueResult dbresult = driver->executeSingleValueQuery(q,
			                                                               result);
		}
		
		void
		DBImpl::
		executeSingleRowQuery(const String& q,
		                      std::map<String, String>&)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
		}
		
		void
		DBImpl::
		executeSingleColQuery(const String& q,
		                      std::vector<String>& result)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
			DBSingleColResult dbresult = driver->executeSingleColQuery(q,
			                                                           result);
		}
		
		void
		DBImpl::
		executeMultiRowQuery(const String& q,
		                     std::vector< std::map<String, String> >&)
		{
			if (driver.get() == NULL)
				initDriver();
			logger.log<LOGGINGTYPE::DEBUG>(q);
		}
	}
}
