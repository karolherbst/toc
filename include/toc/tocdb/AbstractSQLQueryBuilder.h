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

#ifndef LIB_TOCDB_ABSTRACTSQLQUERYBUILDER
#define LIB_TOCDB_ABSTRACTSQLQUERYBUILDER 1

#include <toc/tocdb/AbstractQueryBuilder.h>

namespace TOC
{
	namespace DB
	{
		/*
		 * AbstractSQLQueryBuilder is just a abstract class to make it easier implementing QueryBuilder for SQL
		 * base dbms. all pure methods are listed here just for documentation, so you know what you have to
		 * implement.
		 *
		 * @see TOC::DB::AbstractQueryBuilder
		 */
		class AbstractSQLQueryBuilder : public AbstractQueryBuilder
		{
		public:
			virtual
			const std::string
			entityclass() const override;
			
			virtual
			void
			entityclass(const std::string& entityclass) override;
			
			virtual
			const std::string
			attribute() const override;
			
			virtual
			void
			attribute(const std::string& attribute) override;
			
			virtual
			const uint64_t
			id() const override;
			
			virtual
			void
			id(const uint64_t& id) override;

			virtual
			std::string
			buildCreateEntityClassQuery() = 0;
			
			virtual
			std::string
			buildRelationEntityClassQuery(const std::string& t1,
			                              const std::string& t2) = 0;
			
			virtual
			std::string
			buildSingleAttributeSelectQuery() = 0;
			
			virtual
			std::string
			buildSingleValueInsertQuery(const std::string& attribute) = 0;
			
			virtual
			std::string
			buildIdInsertQuery(std::map<std::string,
			                            std::string>&) = 0;
			
			virtual
			std::string
			buildIDSelectQuery() override;
			
			virtual
			std::string
			buildSingleRowSelectQuery() override;
			
			virtual
			std::string
			startTransaction() override;
			
			virtual
			std::string
			commitTransaction() override;
			
			virtual
			std::string
			rollbackTransaction() override;
			
			virtual
			std::string
			buildSingleValueSelectQuery() override;
			
			virtual
			std::string
			buildDeleteEntityClassQuery(bool ifExists = false) override;
			
			virtual
			std::string
			buildAddAttributeQuery(const std::string& defaultValue,
			                       const std::string& type,
			                       const int16_t size) override;
		protected:
			virtual
			std::string
			replaceASCnDESC(ORDER o);
			
			virtual
			std::string
			replaceType(const std::string& type) = 0;

			template<typename T>
			void buildOrderPart(T& ss);
			
			template<typename T>
			void buildWherePart(T& ss);
		private:
			std::string
			_entityclass;
			
			std::string
			_attribute;
			
			uint64_t
			_id;
		};

		template<typename T>
		void
		AbstractSQLQueryBuilder::
		buildWherePart(T& ss)
		{
			if (keys.size() > 0
			 && keys.size() == values.size())
			{
				ss << " WHERE "
				   << keys.front()
				   << "='"
				   << values.front()
				   << "'";
				keys.pop();
				values.pop();
				for (size_t i = keys.size(); i > 0; i--)
				{
					ss << " AND "
					   << keys.front()
					   << "='"
					   << values.front()
					   << "'";
					keys.pop();
					values.pop();
				}
			}
		}

		template<typename T>
		void
		AbstractSQLQueryBuilder::
		buildOrderPart(T& ss)
		{
			if (orders.size() > 0)
			{
				ss << " ORDER BY "
				   << orders.front().first
				   << ' '
				   << replaceASCnDESC(orders.front().second);
				orders.pop();
				for (size_t i = orders.size(); i > 0; i--)
				{
					ss << ", "
					   << orders.front().first
					   << ' '
					   << replaceASCnDESC(orders.front().second);
					orders.pop();
				}
			}
		}
	}
}

#endif //LIB_TOCDB_ABSTRACTQUERYBUILDER

