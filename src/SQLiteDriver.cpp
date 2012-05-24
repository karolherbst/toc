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

#include <sqlite3.h>
#include "SQLiteDriver.h"

#include <toc/tocdb/DBExceptions.h>

namespace TOC
{
	namespace DB
	{
		template <class Exception>
		void
		SQLiteDriver::
        handleError(uint16_t code,
                    const String &sql)
        {
            switch (code)
            {
            case SQLITE_OK:
                break;
            default:
                StringStream ss;
                ss << sqlite3_errmsg(this->driver) << " (error: " << code
                   << ", extended error: " << sqlite3_extended_errcode(this->driver)
                   << ") in SQL statement: " << sql;
                throw Exception(ss.str());
            }
        }

		SQLiteDriver::
		SQLiteDriver()
		:	driver(nullptr)
		{
			static bool initialized = false;
			if(!initialized)
			{
				sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
				initialized = true;
			}
		}

		SQLiteDriver::
		~SQLiteDriver()
		{
			close();
		}

		void
		SQLiteDriver::
		databaseName(String s)
		{
			this->dbname = s;
		}

		String
		SQLiteDriver::
		databaseName()
		{
			return this->dbname;
		}

		void
		SQLiteDriver::
		close()
		{
			if (sqlite3_close(this->driver) != SQLITE_OK)
				throw CantCloseDBException();
			this->driver = nullptr;
		}

		bool
		SQLiteDriver::
		auth()
		{
			sqlite3_open(this->sqliteFileName().c_str(),
			             &this->driver);
		}

		void
		SQLiteDriver::
		startTransaction()
		{
			
		}

		void
		SQLiteDriver::
		commit()
		{
			
		}

		void
		SQLiteDriver::
		rollback()
		{
			
		}

		bool
		SQLiteDriver::
		exec(const String& query)
		{
			char *error;
			const char *tail;
			struct sqlite3_stmt * stmt;

			int ret = sqlite3_prepare_v2(this->driver,
			                             query.c_str(),
			                             query.size(),
			                             &stmt,
			                             &tail);
			handleError<MalformedQueryException>(ret, query);
			ret = sqlite3_step(stmt);
			if (ret != SQLITE_DONE)
				throw QueryWasMissUsedException("In DBDriver::exec only query without return values are alowed!");
			handleError(ret, query);

			sqlite3_finalize(stmt);
			return ret == SQLITE_OK;
		}

		DBSingleValueResult
		SQLiteDriver::
		executeSingleValueQuery(const String& query,
		                        String& resultHolder)
		{
			
		}

		DBSingleColResult
		SQLiteDriver::
		executeSingleColQuery(const String& q,
		                      std::vector<String>& result)
		{
			
		}

		DBDriver*
		SQLiteDriver::
		newDriver()
		{
			return new SQLiteDriver();
		}

		String
		SQLiteDriver::
		sqliteFileName()
		{
			return this->dbname + ".sqlite";
		}
	}
}
