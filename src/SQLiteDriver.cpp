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
#include "SQLiteQueryBuilder.h"

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
			case SQLITE_DONE:
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
			return sqlite3_open(this->sqliteFileName().c_str(),
			                    &this->driver) == SQLITE_OK;
		}

		void
		SQLiteDriver::
		startTransaction()
		{
			this->exec(SQLiteQueryBuilder().startTransaction());
		}

		void
		SQLiteDriver::
		commit()
		{
			this->exec(SQLiteQueryBuilder().commitTransaction());
		}

		void
		SQLiteDriver::
		rollback()
		{
			this->exec(SQLiteQueryBuilder().rollbackTransaction());
		}

		bool
		SQLiteDriver::
		exec(const String& query)
		{
			const char *tail;
			struct sqlite3_stmt *stmt;

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

		void
		SQLiteDriver::
		executeSingleValueQuery(const String& query,
		                        String& resultHolder)
		{
			const char *tail;
			struct sqlite3_stmt *stmt;

			int ret = sqlite3_prepare_v2(this->driver,
			                             query.c_str(),
			                             query.size(),
			                             &stmt,
			                             &tail);
			this->handleError<MalformedQueryException>(ret, query);
			ret = sqlite3_step(stmt);
			if (ret == SQLITE_OK)
				throw EmptyResultException();
			else if (ret != SQLITE_ROW)
				this->handleError(ret, query);

			resultHolder = this->convertSQLiteTypeToString(stmt,
			                                               0,
			                                               sqlite3_column_type(stmt, 0)
			                                              );
			ret = sqlite3_step(stmt);
			handleError(ret, query);
			sqlite3_finalize(stmt);
		}

		void
		SQLiteDriver::
		executeSingleColQuery(const String& q,
		                      std::vector<String>& result)
		{
			char *error;
			const char *tail;
			struct sqlite3_stmt *stmt;

			int ret = sqlite3_prepare_v2(this->driver,
			                             q.c_str(),
			                             q.size(),
			                             &stmt,
			                             &tail);
			this->handleError<MalformedQueryException>(ret, q);
			ret = sqlite3_step(stmt);
			if (ret == SQLITE_OK)
				throw EmptyResultException();
			else if (ret != SQLITE_ROW)
				this->handleError(ret, q);

			int type = sqlite3_column_type(stmt, 0);
			while ( ret == SQLITE_ROW )
			{
				result.push_back(this->convertSQLiteTypeToString(stmt,
				                                                 0,
				                                                 type));
				ret = sqlite3_step(stmt);
			}
			handleError(ret, q);
			sqlite3_finalize(stmt);
		}

		void
		SQLiteDriver::
		executeSingleRowQuery(const String& q,
		                      std::map<String, String>& result)
		{
			char *error;
			const char *tail;
			struct sqlite3_stmt *stmt;

			int ret = sqlite3_prepare_v2(this->driver,
			                             q.c_str(),
			                             q.size(),
			                             &stmt,
			                             &tail);
			this->handleError<MalformedQueryException>(ret, q);
			ret = sqlite3_step(stmt);
			if (ret == SQLITE_OK)
				throw EmptyResultException();
			else if (ret != SQLITE_ROW)
				this->handleError(ret, q);

			for (int i = 0; i < sqlite3_column_count(stmt); i++)
				result[sqlite3_column_name(stmt, i)] = this->convertSQLiteTypeToString(stmt,
				                                                                       i,
				                                                                       sqlite3_column_type(stmt, i));
			ret = sqlite3_step(stmt);
			handleError(ret, q);
			sqlite3_finalize(stmt);
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

		String
		SQLiteDriver::
		convertSQLiteTypeToString(struct sqlite3_stmt *stmt,
		                          int index,
		                          int type)
		{
			switch (type)
			{
			case SQLITE_INTEGER:
				return lexical_cast<String>(sqlite3_column_int64(stmt, index));
				break;
			case SQLITE_FLOAT:
				return lexical_cast<String>(sqlite3_column_double(stmt, index));
				break;
			case SQLITE_BLOB:
				return lexical_cast<String>(sqlite3_column_bytes16(stmt, index));
				break;
			case SQLITE_TEXT:
				return lexical_cast<String>(sqlite3_column_text(stmt, index));
				break;
			case SQLITE_NULL:
			default:
				return nullptr;
				break;
			}
		}
	}
}
