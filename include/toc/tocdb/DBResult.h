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

#ifndef LIB_TOCDB_DB_DBRESULT
#define LIB_TOCDB_DB_DBRESULT 1

#include <map>
#include <toc/tocstring/TocString.h>
#include <vector>

namespace TOC
{
    namespace DB
    {
        template <typename Type>
        struct DBResult
        {
            DBResult(const Type& result);
            DBResult();
            
            const Type& result;
            const bool empty;
        };
        
        typedef DBResult<bool>                                                  DBBoolResult;
        typedef DBResult<String>                                           DBSingleValueResult;
        typedef DBResult<std::map<String, String> >                   DBSingleRowResult;
        typedef DBResult<std::vector<String> >                             DBSingleColResult;
        typedef DBResult<std::vector< std::map<String, String> > >    DBMultiRowResult;
        
        template <typename T>
        DBResult<T>::
        DBResult(const T& _result)
        :   result(_result),
        empty(false)
        {
            
        }
        
        template <typename T>
        DBResult<T>::
        DBResult()
        :   result(),
        empty(true)
        {
            
        }
    }
}

#endif //LIB_TOCDB_DB_DBRESULT
