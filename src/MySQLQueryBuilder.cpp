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
		String replaceASCnDESC(ORDER o)
		{
			return o == ORDER::ASC ? "ASC" : "DESC";
		}
		
		String replaceType(const String& type)
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
		
		String
		MySQLQueryBuilder::
		startTransaction()
		{
			return "START TRANSACTION;";
		}
		
		String
		MySQLQueryBuilder::
		commitTransaction()
		{
			return "COMMIT;";
		}
		
		String
		MySQLQueryBuilder::
		rollbackTransaction()
		{
			return "ROLLBACK;";
		}
		
		String
		MySQLQueryBuilder::
		buildCreateEntityClassQuery()
		{
			std::stringstream ss;
			ss << "CREATE TABLE " << entityclass()
			   << " (ID INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY(ID) ) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
			return ss.str();
		}
		
		String
		MySQLQueryBuilder::
		buildRelationEntityClassQuery(const String& t1,
		                              const String& t2)
		{
			std::stringstream ss;
			ss << "CREATE TABLE " << entityclass() << " ("
			   << t1 << " INT UNSIGNED NOT NULL, "
			   << t2 << " INT UNSIGNED NOT NULL, PRIMARY KEY ("
			   << t1 << ", " << t2 << "), CONSTRAINT "
			   << t1 << " FOREIGN KEY (" << t1 << ") REFERENCES "
			   << t1 << " (ID) ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT "
			   << t2 << " FOREIGN KEY (" << t2 << ") REFERENCES " << t2
			   << " (ID) ON DELETE RESTRICT ON UPDATE CASCADE) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
			return ss.str();
		}
		
		String
		MySQLQueryBuilder::
		buildAddAttributeQuery(const String& defaultValue,
		                       const String& type,
		                       const int16_t size)
		{
			std::stringstream ss;
			ss << "ALTER TABLE " << entityclass() << " ADD COLUMN " << attribute()
			   << replaceType(type) << '(' << size << ") " << "DEFAULT '"
			   << defaultValue << "';";
			return ss.str();
		}
		
		String
		MySQLQueryBuilder::
		buildIDSelectQuery()
		{
			std::stringstream ss;
			ss << "SELECT ID FROM " << entityclass();
			buildWherePart(ss);
			buildOrderPart(ss);
			ss << ';';
			return ss.str();
		}
		
		String
		MySQLQueryBuilder::
		buildSingleValueSelectQuery()
		{
			std::stringstream ss;
			ss << "SELECT " << attribute() << " FROM " << entityclass() << " WHERE ID='"
			   << id() << "';";
			return ss.str();
		}
		
		String
		MySQLQueryBuilder::
		buildSingleAttributeSelectQuery()
		{
			std::stringstream ss;
			ss << "SELECT " << attribute() << " FROM " << entityclass();
			buildWherePart(ss);
			buildOrderPart(ss);
			ss << ';';
			return ss.str();
		}
		
		String
		MySQLQueryBuilder::
		buildSingleValueInsertQuery(const String& v)
		{
			std::stringstream ss;
			ss << "INSERT INTO " << entityclass() << " (ID, " << attribute()
			   << ") VALUES ('" << id() << "', '" << v << "') ON DUPLICATE KEY UPDATE "
			   << attribute() << "='" << v << "';";
			return ss.str();
		}
		
		String
		MySQLQueryBuilder::
		buildIdInsertQuery(std::map<String, String>& values)
		{
			std::stringstream ss;
			if (values.size() > 0)
			{
				typedef std::pair<String, String> Pair;
				ss << "INSERT INTO " << entityclass() << " (" << values.begin()->first;
				
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
				
				ss << "') ON DUPLICATE KEY UPDATE ";
				
				ss << values.begin()->first << "='" << values.begin()->second << '\'';
				
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
						ss << ", " << p.first << "='" << p.second << '\'';
					}
				}
				
				ss << ';';
			}
			return ss.str();
		}
		
		template<class T>
		void
		MySQLQueryBuilder::
		buildWherePart(T& ss)
		{
			if (keys.size() > 0 && keys.size() == values.size())
			{
				ss << " WHERE ";
				ss << keys.front() << "='" << values.front() << "'";
				keys.pop();
				values.pop();
				for (size_t i = keys.size(); i > 0; i--)
				{
					ss << " AND " << keys.front() << "='" << values.front()
					<< "'";
					keys.pop();
					values.pop();
				}
			}
		}
		
		template<class T>
		void
		MySQLQueryBuilder::
		buildOrderPart(T& ss)
		{
			if (orders.size() > 0)
			{
				ss << " ORDER BY " << orders.front().first << ' '
				<< replaceASCnDESC(orders.front().second);
				orders.pop();
				for (size_t i = orders.size(); i > 0; i--)
				{
					ss << ", " << orders.front().first << ' '
					<< replaceASCnDESC(orders.front().second);
					orders.pop();
				}
			}
		}

		const uint64_t
		MySQLQueryBuilder::
		id() const
		{
			return _id;
		}

		void
		MySQLQueryBuilder::
		id(const uint64_t &i)
		{
			_id = i;
		}

		const String
		MySQLQueryBuilder::
		attribute() const
		{
			return _attribute;
		}

		void
		MySQLQueryBuilder::
		attribute(const String &a)
		{
			_attribute = a;
		}

		const String
		MySQLQueryBuilder::
		entityclass() const
		{
			return _entityclass;
		}

		void
		MySQLQueryBuilder::
		entityclass(const String &e)
		{
			_entityclass = e;
		}

		AbstractQueryBuilder*
		MySQLQueryBuilder::
		newQueryBuilder()
		{
			return new MySQLQueryBuilder();
		}
	}
}

