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

#include <mysql++/mysql++.h>

#include <toc/tocdb/DBDriver.h>
#include <toc/tocstring/TocString.h>

namespace TOC
{
	namespace DB
	{
		class MySQLDriver : public DBDriver
		{
		public:
			MySQLDriver();
			~MySQLDriver();

			virtual
			void
			databaseName(std::string) override;
            
			virtual
			std::string
			databaseName() override;
            
			virtual
			void
			userName(std::string) override;
            
			virtual
			std::string
			userName() override;
            
			virtual
			void
			userPassword(std::string) override;
            
			virtual
			std::string
			userPassword() override;
            
			virtual
			void
			serverURL(std::string) override;
            
			virtual
			std::string
			serverURL() override;
            
			virtual
			void
			serverPort(uint16_t) override;
			
            virtual
            uint16_t
            serverPort() override;
            
		private:
			std::string
			dbname;
			
			std::string
			uname;
			
			std::string
			pw;
			
			std::string
			url;
			
			uint16_t
			port;

		public:
			void
			close();
			/*
			 * return true if auth was successfull
			 * return false if connected without authentication
			 * throws CoreException if authentication fails
			 */
			bool
			auth();
			
			void
			startTransaction();
			
			void
			commit();
			
			void
			rollback();
			
			bool
			exec(const std::string&);
			
			void
			executeSingleValueQuery(const std::string& query,
			                        std::string& resultHolder);
			
			void
			executeSingleColQuery(const std::string& q,
			                      std::vector<std::string>& result);
			
			// not in interface:
			void
			handleMYSQLerrno(int32_t,
			                 const char* message);
			
			void
			executeSingleRowQuery(const std::string& q,
			                      std::map<std::string,
			                               std::string>& result);

			static
			DBDriver*
			newDriver();
			
		private:
			mysqlpp::Connection*
			conn;
			
			mysqlpp::SimpleResult
			execute(const std::string&);
			
			mysqlpp::StoreQueryResult
			store(const std::string&);
		};
	}
}

