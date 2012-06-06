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
#include <boost/foreach.hpp>

#define foreach		 BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

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
			return "";
		}

		String
		SQLiteQueryBuilder::
		buildIDSelectQuery()
		{
			std::stringstream ss;
			ss << "SELECT * FROM " << entityclass() << " WHERE ID='" << id() << "';";
			return ss.str();
		}

		String
		SQLiteQueryBuilder::
		buildIdInsertQuery(std::map<String, String>& values)
		{
			std::stringstream ss;
			if (values.size() > 0)
			{
				typedef std::pair<String, String> Pair;
				ss << "INSERT OR REPLACE INTO " << entityclass() << " (" << values.begin()->first;
				
				if (values.size() > 1)
				{
					bool tmp = true;
					foreach(const Pair& p, values)
					{
						if (tmp)
						{
							tmp = false;
							continue;
						}
						ss << ", " << p.first;
					}
				}
				ss << ") VALUES ('" << values.begin()->second;
				
				if (values.size() > 1)
				{
					bool tmp = true;
					foreach(const Pair& p, values)
					{
						if (tmp)
						{
							tmp = false;
							continue;
						}
						ss << "', '" << p.second;
					}
				}
				
				ss << "');";
			}
			return ss.str();
		}

		String
		SQLiteQueryBuilder::
		buildRelationEntityClassQuery(const String&,
		                                     const String&)
		{
			return "";
		}

		String
		SQLiteQueryBuilder::
		buildSingleValueInsertQuery(const String& v)
		{
			std::stringstream ss;
			ss << "UPDATE OR REPLACE " << entityclass() << " SET " << attribute()
			   << "='" << v << "' WHERE ID='" << id() << "';";
			return ss.str();
		}

		String
		SQLiteQueryBuilder::
		startTransaction()
		{
			return "BEGIN TRANSACTION;";
		}

		AbstractQueryBuilder*
		SQLiteQueryBuilder::
		newQueryBuilder()
		{
			return new SQLiteQueryBuilder();
		}
	}
}
