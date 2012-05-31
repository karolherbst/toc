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

#include "SQLiteQueryBuilder.h"

#include <toc/tocdb/StandardTypes.h>

namespace TOC
{
	namespace DB
	{
		String
		SQLiteQueryBuilder::
        replaceType(const String& type)
   	    {
       	    if (type == DBInt)
           	    return " INT";
            if (type == DBString)
   	            return " TEXT";
       	    if (type == DBFloat)
           	    return " REAL";
            if (type == DBText)
   	            return " TEXT";
       	    return "";
        }

		String
		SQLiteQueryBuilder::
		buildCreateEntityClassQuery()
		{
			std::stringstream ss;
			ss << "CREATE TABLE " << entityclass()
				// we use INTEGER here, because it will be an alias for the internal rowid used by sqlite
			   << " (ID INTEGER NOT NULL PRIMARY KEY ASC AUTOINCREMENT);";
			return ss.str();
		}

		String
		SQLiteQueryBuilder::
		buildSingleAttributeSelectQuery()
		{

		}

		String
		SQLiteQueryBuilder::
		buildIDSelectQuery()
		{

		}

		String
		SQLiteQueryBuilder::
		buildIdInsertQuery(std::map<String, String>&)
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildRelationEntityClassQuery(const String&,
		                                     const String&)
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildAddAttributeQuery(const String& defaultValue,
		                              const String& _type,
		                              const int16_t size)
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildSingleValueInsertQuery(const String&)
		{
			
		}

		String
		SQLiteQueryBuilder::
		startTransaction()
		{
			return "BEGIN TRANSACTION;";
		}

		const uint64_t
		SQLiteQueryBuilder::
		id() const
		{
			return this->_id;
		}

		void
		SQLiteQueryBuilder::
		id(const uint64_t &i)
		{
			this->_id = i;
		}

		const String
		SQLiteQueryBuilder::
		attribute() const
		{
			return this->_attribute;
		}

		void
		SQLiteQueryBuilder::
		attribute(const String &s)
		{
			this->_attribute = s;
		}

		const String
		SQLiteQueryBuilder::
		entityclass() const
		{
			return this->_entityclass;
		}

		void
		SQLiteQueryBuilder::
		entityclass(const String& s)
		{
			this->_entityclass = s;
		}
		
		AbstractQueryBuilder*
		SQLiteQueryBuilder::
		newQueryBuilder()
		{
			return new SQLiteQueryBuilder();
		}
	}
}
