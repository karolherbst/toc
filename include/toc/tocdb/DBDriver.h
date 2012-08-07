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

#ifndef LIB_TOCDB_DB_DBDRIVER
#define LIB_TOCDB_DB_DBDRIVER 1

#include <map>
#include <stdint.h>
#include <vector>

#include <boost/noncopyable.hpp>

#include <toc/tocstring/TocString.h>


namespace TOC
{
	namespace DB
	{
		class DBDriver : boost::noncopyable
		{
		public:
			inline virtual
			~DBDriver(){};
			
			inline virtual
			void
			databaseName(std::string){};
			
			inline virtual
			std::string
			databaseName();
			
			inline virtual
			void
			userName(std::string){};
			
			inline virtual
			std::string
			userName();
			
			inline virtual
			void
			userPassword(std::string){};
			
			inline virtual
			std::string
			userPassword();
			
			inline virtual
			void
			serverURL(std::string){};
			
			inline virtual
			std::string
			serverURL();
			
			inline virtual
			void
			serverPort(uint16_t){};
			
			inline virtual
			uint16_t
			serverPort();
			
			virtual
			void
			close() = 0;
			
			/*
			 * return true if auth was successfull
			 * return false if connected without authentication
			 * throws CoreException if authentication fails
			 */
			virtual
			bool
			auth() = 0;
			
			virtual
			void
			startTransaction() = 0;
			
			virtual
			void
			commit() = 0;
			
			virtual
			void
			rollback() = 0;
			
			virtual
			bool
			exec(const std::string&) = 0;
			
			virtual
			void
			executeSingleValueQuery(const std::string& query,
			                        std::string& resultHolder) = 0;
			
			virtual
			void
			executeSingleColQuery(const std::string& q,
			                      std::vector<std::string>& result) = 0;
			
			virtual
			void
			executeSingleRowQuery(const std::string& q,
			                      std::map<std::string,
			                               std::string>& result) = 0;
		};
		
		std::string
		DBDriver::
		databaseName()
		{
			return std::string();
		}
		
		std::string
		DBDriver::
		userName()
		{
			return std::string();
		}
		
		std::string
		DBDriver::
		userPassword()
		{
			return std::string();
		}
		
		std::string
		DBDriver::
		serverURL()
		{
			return std::string();
		}
		
		uint16_t
		DBDriver::
		serverPort()
		{
			return 0;
		}
	}
}

#endif //LIB_TOCDB_DB_DBDRIVER

