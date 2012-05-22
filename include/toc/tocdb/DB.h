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

#include <boost/thread/tss.hpp>
#include <loki/Singleton.h>
#include <map>
#include <toc/tocdb/DBResource.h>
#include <toc/toclogger.h>
#include <toc/tocstring/TocString.h>

CREATE_LOGGER_NAME_CLASS_DEF(DBLog);

#include <toc/boost/extension/impl/decl.hpp>
#ifndef DLL_TOC_DB
#ifdef MAKE_TOC_DB
#define DLL_TOC_DB BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_DB BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

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
        
        class DLL_TOC_DB DBImpl
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
            
            void setConnectionInfo(String& server,
                                   uint32_t port,
                                   String& user,
                                   String& pw,
                                   String& db);

			template <typename ST>
            void setDatabaseName(const ST&);

			template <typename ST>
            void setUserName(const ST&);

			template <typename ST>
            void setUserPassword(const ST&);

			template <typename ST>
            void setServerURL(const ST&);

            void setServerPort(uint32_t);
            
            // db accessing
            DBTable operator[](const String&);
            
            void createTransaction();
            void commit();
            void rollback();
            
            void executeQuery(const String&);
            void executeBoolQuery(const String&, bool&);
            void executeSingleValueQuery(const String&, String&);
            void executeSingleRowQuery(const String&, std::map<String, String>&);
            void executeSingleColQuery(const String&, std::vector<String>&);
            void executeMultiRowQuery(const String&, std::vector< std::map<String, String> >&);
        private:
            void Open();
            void close();
            
            String db, user, pw, url;
            uint32_t port;
            
            CREATE_LOGGER(logger, DBLog);
            boost::thread_specific_ptr<DBDriver> driver;
        };
        
        typedef Loki::SingletonHolder<DBImpl> DB;
        
        // TOC::DB::Instance() is simpler than TOC::DB::DB::Instance()
        inline DBImpl& Instance()
        {
            return TOC::DB::DB::Instance();
        }

		template <typename ST>
		void
        DBImpl::
        setDatabaseName(const ST& _db)
        {
            db = _db;
        }

		template <typename ST>
        void
        DBImpl::
        setUserName(const ST& name)
        {
            user = name;
        }

		template <typename ST>
        void
        DBImpl::
        setUserPassword(const ST& _pw)
        {
            pw = _pw;
        }

		template <typename ST>
        void
        DBImpl::
        setServerURL(const ST& _url)
        {
            url = _url;
        }
    }
}

#endif //LIB_TOCDB_DB
