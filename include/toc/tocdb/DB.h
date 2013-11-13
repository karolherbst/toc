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

#ifndef LIB_TOCDB_DB
#define LIB_TOCDB_DB 1

#include <map>

#include <boost/thread/tss.hpp>
#include <loki/Singleton.h>

#include <toc/tocdb/DBResource.h>
#include <toc/tocstring/TocString.h>

namespace boost
{
	namespace extensions
	{
		class shared_library;
	}
}

namespace TOC
{
	namespace DB
	{
		class AbstractQueryBuilder;
		class DBDriver;
		class DBTable;
		
		class DBImpl
		{
			friend class DBTable;
			friend class DBCol;
			friend class DBRow;
			friend class DBValue;
			friend class DBDriver;
		public:
			DBImpl();
			~DBImpl();
			
			void initDriver();
			
			void setConnectionInfo(std::string& server,
								   uint32_t port,
								   std::string& user,
								   std::string& pw,
								   std::string& db);

			template <typename StringType>
			void
			setDatabaseName(const StringType&);

			template <typename StringType>
			void
			setUserName(const StringType&);

			template <typename StringType>
			void
			setUserPassword(const StringType&);

			template <typename StringType>
			void
			setServerURL(const StringType&);

			void
			setServerPort(uint32_t);
			
			// db accessing
			DBTable
			operator[](const std::string&);
			
			void
			createTransaction();
			
			void
			commit();
			
			void
			rollback();
			
			void
			executeQuery(const std::string&);
			
			void
			executeBoolQuery(const std::string&,
			                 bool&);
			
			void
			executeSingleValueQuery(const std::string&,
			                        std::string&);
			
			void
			executeSingleRowQuery(const std::string&,
			                      std::map<std::string,
			                               std::string>&);
			
			void
			executeSingleColQuery(const std::string&,
			                      std::vector<std::string>&);
			
			void
			executeMultiRowQuery(const std::string&,
			                     std::vector<std::map<std::string,
			                                          std::string>>&);
			
		private:
			void
			Open();
			
			void
			close();
			
			std::string
			db;
			
			std::string
			user;
			
			std::string
			pw;
			
			std::string
			url;
			
			uint32_t
			port;
			
			boost::thread_specific_ptr<DBDriver>
			driver;
		};
		
		typedef Loki::SingletonHolder<DBImpl> DB;
		
		// TOC::DB::Instance() is simpler than TOC::DB::DB::Instance()
		inline DBImpl& Instance()
		{
			return TOC::DB::DB::Instance();
		}

		template <typename StringType>
		void
		DBImpl::
		setDatabaseName(const StringType& _db)
		{
			this->db = _db;
		}

		template <typename StringType>
		void
		DBImpl::
		setUserName(const StringType& name)
		{
			this->user = name;
		}

		template <typename StringType>
		void
		DBImpl::
		setUserPassword(const StringType& pw)
		{
			this->pw = pw;
		}

		template <typename StringType>
		void
		DBImpl::
		setServerURL(const StringType& url)
		{
			this->url = url;
		}
	}
}

#endif //LIB_TOCDB_DB

