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

#include <toc/tocdb/AbstractSQLQueryBuilder.h>

namespace TOC
{
	namespace DB
	{
		std::string
		AbstractSQLQueryBuilder::
		replaceASCnDESC(ORDER o)
        {
            return o == ORDER::ASC ? "ASC" : "DESC";
        }

        std::string
		AbstractSQLQueryBuilder::
        startTransaction()
        {
            return "START TRANSACTION;";
        }
         
        std::string
		AbstractSQLQueryBuilder::
        commitTransaction()
        {
            return "COMMIT;";
        }
         
        std::string
		AbstractSQLQueryBuilder::
        rollbackTransaction()
        {
            return "ROLLBACK;";
        }

		std::string
        AbstractSQLQueryBuilder::
        buildSingleValueSelectQuery()
        {
            std::stringstream ss;
            ss << "SELECT "
               << attribute()
               << " FROM "
               << entityclass()
               << " WHERE ID='"
               << id()
               << "';";
            return ss.str();
        }

		std::string
        AbstractSQLQueryBuilder::
		buildDeleteEntityClassQuery(bool ifExists)
		{
			std::stringstream ss;
			ss << "DROP TABLE ";
			if (ifExists)
				ss << "IF EXISTS ";
			ss << entityclass() << ";";
			return ss.str();
		}

		std::string
        AbstractSQLQueryBuilder::
        buildAddAttributeQuery(const std::string& defaultValue,
                               const std::string& type,
                               const int16_t size)
        {
            std::stringstream ss;
            ss << "ALTER TABLE "
               << entityclass()
               << " ADD COLUMN "
               << attribute()
               << replaceType(type)
               << '('
               << size
               << ") "
               << "DEFAULT '"
               << defaultValue
               << "';";
            return ss.str();
        }

		std::string
		AbstractSQLQueryBuilder::
		buildSingleRowSelectQuery()
		{
			std::stringstream ss;
			ss << "SELECT * FROM "
			   << entityclass()
			   << " WHERE ID='"
			   << id()
			   << "';";
			return ss.str();
		}

		std::string
		AbstractSQLQueryBuilder::
		buildIDSelectQuery()
		{
			std::stringstream ss;
			ss << "SELECT ID FROM " << entityclass();
			buildWherePart(ss);
			buildOrderPart(ss);
			ss << ';';
			return ss.str();
		}

		const uint64_t
        AbstractSQLQueryBuilder::
		id() const
		{
			return this->_id;
		}

		void
        AbstractSQLQueryBuilder::
		id(const uint64_t &i)
		{
			this->_id = i;
		}

		const std::string
        AbstractSQLQueryBuilder::
		attribute() const
		{
			return this->_attribute;
		}

		void
        AbstractSQLQueryBuilder::
		attribute(const std::string &s)
		{
			this->_attribute = s;
		}

		const std::string
        AbstractSQLQueryBuilder::
		entityclass() const
		{
			return this->_entityclass;
		}

		void
        AbstractSQLQueryBuilder::
		entityclass(const std::string& s)
		{
			this->_entityclass = s;
		}
	}
}
