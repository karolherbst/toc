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

#include <stdint.h>
#include <toc/tocstring/TocString.h>
#include <toc/tocdb/DBResult.h>
#include <vector>

#include <toc/boost/extension/impl/decl.hpp>
#ifndef DLL_TOC_DB
#ifdef MAKE_TOC_DB
#define DLL_TOC_DB BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_DB BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace TOC
{
    namespace DB
    {
        class DLL_TOC_DB DBDriver
        {
        public:
            virtual ~DBDriver();
            
            String& databaseName();
            String& userName();
            String& userPassword();
            String& serverURL();
            uint32_t& serverPort();
            
            virtual void close() = 0;
            /*
             * return true if auth was successfull
             * return false if connected without authentication
             * throws CoreException if authentication fails
             */
            virtual bool auth() = 0;
            
            virtual void startTransaction() = 0;
            virtual void commit() = 0;
            virtual void rollback() = 0;
            virtual bool exec(const String&) = 0;
            virtual DBSingleValueResult executeSingleValueQuery(const String& query,
                                                                String& resultHolder) = 0;
            virtual DBSingleColResult executeSingleColQuery(const String& q,
                                                            std::vector<String>& result) = 0;
        private:
            String _databaseName;
            String _userName;
            String _userPassword;
            String _serverURL;
            uint32_t _serverPort;
        };
    }
}

#endif //LIB_TOCDB_DB_DBDRIVER
