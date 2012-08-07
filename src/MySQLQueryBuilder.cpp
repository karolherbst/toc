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

#include "MySQLQueryBuilder.h"

#include <boost/foreach.hpp>

#define foreach		 BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

namespace TOC
{
	namespace DB
	{
		std::string
		MySQLQueryBuilder::
		replaceType(const std::string& type)
		{
			if (type == DBInt)
				return " INT";
			if (type == DBString)
				return " VARCHAR";
			if (type == DBFloat)
				return " FLOAT";
			if (type == DBText)
				return " TEXT";
			return " VARCHAR";
		}

		std::string
		MySQLQueryBuilder::
		buildCreateEntityClassQuery()
		{
			std::stringstream ss;
			ss << "CREATE TABLE "
			   << entityclass()
			   << " (ID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
			return ss.str();
		}
		
		std::string
		MySQLQueryBuilder::
		buildRelationEntityClassQuery(const std::string& t1,
		                              const std::string& t2)
		{
			std::stringstream ss;
			ss << "CREATE TABLE "
			   << entityclass()
			   << " ("
			   << t1
			   << " INT UNSIGNED NOT NULL, "
			   << t2
			   << " INT UNSIGNED NOT NULL, PRIMARY KEY ("
			   << t1
			   << ", "
			   << t2
			   << "), CONSTRAINT "
			   << t1
			   << " FOREIGN KEY ("
			   << t1
			   << ") REFERENCES "
			   << t1
			   << " (ID) ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT "
			   << t2
			   << " FOREIGN KEY ("
			   << t2
			   << ") REFERENCES "
			   << t2
			   << " (ID) ON DELETE RESTRICT ON UPDATE CASCADE) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
			return ss.str();
		}
		
		std::string
		MySQLQueryBuilder::
		buildSingleAttributeSelectQuery()
		{
			std::stringstream ss;
			ss << "SELECT "
			   << attribute()
			   << " FROM "
			   << entityclass();
			buildWherePart(ss);
			buildOrderPart(ss);
			ss << ';';
			return ss.str();
		}
		
		std::string
		MySQLQueryBuilder::
		buildSingleValueInsertQuery(const std::string& v)
		{
			std::stringstream ss;
			ss << "INSERT INTO "
			   << entityclass()
			   << " (ID, "
			   << attribute()
			   << ") VALUES ('"
			   << id()
			   << "', '"
			   << v
			   << "') ON DUPLICATE KEY UPDATE "
			   << attribute()
			   << "='"
			   << v
			   << "';";
			return ss.str();
		}
		
		std::string
		MySQLQueryBuilder::
		buildIdInsertQuery(std::map<std::string,
		                            std::string>& values)
		{
			std::stringstream ss;
			if (values.size() > 0)
			{
				typedef std::pair<std::string,
				                  std::string>
				        Pair;
				
				ss << "INSERT INTO "
				   << entityclass()
				   << " ("
				   << values.begin()->first;
				
				if (values.size() > 1)
				{
					bool tmp = true;
					foreach(const Pair& p,
					        values)
					{
						if (tmp)
						{
							tmp = false;
							continue;
						}
						ss << ", "
						   << p.first;
					}
				}
				ss << ") VALUES ('"
				   << values.begin()->second;
				
				if (values.size() > 1)
				{
					bool tmp = true;
					foreach(const Pair& p,
					        values)
					{
						if (tmp)
						{
							tmp = false;
							continue;
						}
						ss << "', '"
						   << p.second;
					}
				}
				
				ss << "') ON DUPLICATE KEY UPDATE "
				   << values.begin()->first
				   << "='"
				   << values.begin()->second
				   << '\'';
				
				if (values.size() > 1)
				{
					bool tmp = true;
					foreach(const Pair& p,
					        values)
					{
						if (tmp)
						{
							tmp = false;
							continue;
						}
						ss << ", "
						   << p.first
						   << "='"
						   << p.second
						   << '\'';
					}
				}
				ss << ';';
			}
			return ss.str();
		}

		AbstractQueryBuilder*
		MySQLQueryBuilder::
		newQueryBuilder()
		{
			return new MySQLQueryBuilder();
		}
	}
}

