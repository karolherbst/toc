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
		std::string
		SQLiteQueryBuilder::
        replaceType(const std::string& type)
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

		std::string
		SQLiteQueryBuilder::
		buildCreateEntityClassQuery()
		{
			std::stringstream ss;
			ss << "CREATE TABLE "
			   << entityclass()
				// we use INTEGER here, because it will be an alias for the internal rowid used by sqlite
			   << " (ID INTEGER NOT NULL PRIMARY KEY ASC AUTOINCREMENT);";
			return ss.str();
		}

		std::string
		SQLiteQueryBuilder::
		buildSingleAttributeSelectQuery()
		{
			return "";
		}

		std::string
		SQLiteQueryBuilder::
		buildIdInsertQuery(std::map<std::string,
		                            std::string>& values)
		{
			std::stringstream ss;
			if (values.size() > 0)
			{
				typedef std::pair<std::string, std::string> Pair;
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

		std::string
		SQLiteQueryBuilder::
		buildRelationEntityClassQuery(const std::string&,
		                              const std::string&)
		{
			throw MethodNotImplementedException();
			return "";
		}

		std::string
		SQLiteQueryBuilder::
		buildSingleValueInsertQuery(const std::string& v)
		{
			std::stringstream ss;
			ss << "INSERT OR IGNORE INTO "
			   << entityclass()
			   << " (ID) VALUES ('"
			   << id()
			   << "'); "
			   << "UPDATE "
			   << entityclass()
			   << " SET "
			   << attribute()
			   << "='"
			   << v
			   << "' WHERE ID='"
			   << id()
			   << "';";
			return ss.str();
		}

		std::string
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
