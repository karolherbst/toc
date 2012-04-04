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

#ifndef LIB_TOCDB_DB_DBVALUE
#define LIB_TOCDB_DB_DBVALUE 1

#include <ostream>
#include <toc/tocstring/TocString.h>

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
        
        class DLL_TOC_DB DBValue
        {
        public:
            DBValue(AbstractQueryBuilder&);
            
            // convertable to all
            // template <class T>
            // operator T() const;
            
            DBValue& operator=(const String& value);
            
            friend std::ostream&
            operator<<(std::ostream& ostr,
                       const DBValue& m);
        private:
            String convert() const;
            AbstractQueryBuilder& qb;
        };
        
        /*template <class T>
        DBValue::
        operator T() const
        {
            return lexical_cast<T>(convert());
        }*/
        
    }
}

#endif //LIB_TOCDB_DB_DBVALUE
