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

#include <toc/tocdb/DBTable.h>

#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBCol.h>
#include <toc/tocdb/DBResource.h>
#include <toc/tocdb/DBRow.h>
#include <toc/tocdb/AbstractQueryBuilder.h>

namespace TOC
{
    namespace DB
    {
        DBTable::
        DBTable(const String table)
        {
            qb = DBResource::newQueryBuilder();
            qb->entityclass(table);
        }
        
        DBTable::
        ~DBTable()
        {
            delete qb;
        }
        
        DBCol
        DBTable::
        operator[](const String& col)
        {
            return DBCol(col,
                         *qb);
        }
        
        DBRow
        DBTable::
        operator[](const uint64_t row)
        {
            return DBRow(row,
                         *qb);
        }
        
        DBTable&
        DBTable::
        create()
        {
            DB::Instance().executeQuery(qb->buildCreateEntityClassQuery());
            return *this;
        }
        
        DBTable
        DBTable::
        connectWith(const String& t)
        {
            DBTable ret( qb->entityclass() + '_' + t );
            DB::Instance().executeQuery(ret.qb->buildRelationEntityClassQuery(qb->entityclass(),
                                                                              t));
            return ret;
        }
        
        DBTable&
        DBTable::
        insert(std::map<String, String>& values)
        {
            DB::Instance().executeQuery(qb->buildIdInsertQuery(values));
            return *this;
        }
    }
}
