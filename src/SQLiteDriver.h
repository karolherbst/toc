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

#include <toc/tocdb/DBDriver.h>

namespace TOC
{
	namespace DB
	{
		class DBException;

		class SQLiteDriver : public DBDriver
		{
		public:
			virtual
			void
			databaseName(std::string) override;
            
			virtual
			std::string
			databaseName() override;

			SQLiteDriver();
			virtual ~SQLiteDriver() override;

			
			virtual
			void
			close() override;
			
			virtual
			bool
			auth() override;
			
			virtual
			void
			startTransaction() override;
			
			virtual
			void
			commit() override;
			
			virtual
			void
			rollback() override;
			
			virtual
			bool
			exec(const std::string&) override;
			
			virtual
			void
			executeSingleValueQuery(const std::string& query,
			                        std::string& resultHolder) override;
			
			virtual
			void
			executeSingleColQuery(const std::string& q,
			                      std::vector<std::string>& result) override;
			
			virtual
			void
			executeSingleRowQuery(const std::string& q,
			                      std::map<std::string,
			                               std::string>& result) override;
			
			static DBDriver* newDriver();

		private:
			struct sqlite3
			*driver;

			std::string
			dbname;
			
			std::string
			sqliteFileName();

			template <typename Exception = DBException>
	        void
	        handleError(uint16_t,
                        const std::string& sql);
            
			std::string
			convertSQLiteTypeToString(struct sqlite3_stmt *stmt,
			                          int index,
			                          int type);
		};
	}
}

