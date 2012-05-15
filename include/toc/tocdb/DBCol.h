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

#ifndef LIB_TOCDB_DB_DBCOL
#define LIB_TOCDB_DB_DBCOL 1

#include <toc/tocdb/DBTypes.h>
#include <toc/tocdb/StandardTypes.h>
#include <toc/tocstring/TocString.h>
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
        class AbstractQueryBuilder;
        class DBValue;
        
        class DLL_TOC_DB DBCol
        {
        public:
            DBCol(const String& col,
                  AbstractQueryBuilder&);
            
            DBValue operator[](uint64_t id);
            
            DBCol& create(const String& defaultValue = NULLSTRING,
                          const String& type = DBString,
                          const int16_t size = 10);
            
            // query building
            DBCol& where(const String& att,
                         const String value);
            DBCol& order(const String& att,
                         ORDER order);
            
            // search over value
            uint64_t search(const String& value);
            // store values in vec
            DBCol& operator>>(std::vector<String>& vec);
            
        private:
            String orderAtt;
            ORDER orderKind;
            
            AbstractQueryBuilder& qb;
        };
    }
}

#endif //LIB_TOCDB_DB_DBCOL
