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

			virtual void databaseName(String) override;
            virtual String databaseName() override;
            virtual void userName(String) override;
            virtual String userName() override;
            virtual void userPassword(String) override;
            virtual String userPassword() override;
            virtual void serverURL(String) override;
            virtual String serverURL() override;
            virtual void serverPort(uint16_t) override;
            virtual uint16_t serverPort() override;
		private:
			String dbname;
			String uname;
			String pw;
			String url;
			uint16_t port;

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
			exec(const String&);
			
			DBSingleValueResult
			executeSingleValueQuery(const String& query,
			                        String& resultHolder);
			
			DBSingleColResult
			executeSingleColQuery(const String& q,
			                      std::vector<String>& result);
			
			// not in interface:
			void
			handleMYSQLerrno(int32_t,
			                 const char* message);
			
			static
			DBDriver*
			newDriver();
		private:
			mysqlpp::Connection*
			conn;
			
			mysqlpp::SimpleResult
			execute(const String&);
			
			mysqlpp::StoreQueryResult
			store(const String&);
		};
	}
}
