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

#ifndef LIB_TOCDB_DB_DBQUERYINFORMATION
#define LIB_TOCDB_DB_DBQUERYINFORMATION 1

#include <map>
#include <toc/tocstring/TocString.h>
#include <vector>

#include <boost/extension/impl/decl.hpp>
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
        class AbstractQueryBuilder;
        class DBCol;
        class DBRow;
        
        class DLL_TOC_DB DBTable
        {
        public:
            DBTable(const String str);
            ~DBTable();
            
            DBCol operator[](const String& col);
            DBRow operator[](const uint64_t);
            
            DBTable& create();
            DBTable connectWith(const String&);
            DBTable& insert(std::map<String, String>&);
            
            template <typename T>
            DBTable& operator>>(std::vector<T>& vec);
            
        private:
            AbstractQueryBuilder* qb;
        };
        
        template <typename T>
        DBTable&
        DBTable::
        operator>>(std::vector<T>& /*ver*/)
        {
            return *this;
        }
    }
}

#endif //LIB_TOCDB_DB_DBQUERYINFORMATION
