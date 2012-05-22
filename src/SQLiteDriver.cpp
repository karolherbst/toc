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

CREATE_LOGGER_NAME_CLASS_IMPL(SQLiteLog, CSTRING("SQLite"));

namespace TOC
{
	namespace DB
	{
		SQLiteDriver::
		SQLiteDriver()
		:	driver(nullptr)
		{}

		SQLiteDriver::
		~SQLiteDriver()
		{
			close();
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
			sqlite3_open(this->databaseName().c_str(),
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
		exec(const String&)
		{
			
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
	}
}
