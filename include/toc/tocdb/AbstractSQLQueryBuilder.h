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
        class DLL_TOC_DB AbstractSQLQueryBuilder : public AbstractQueryBuilder
        {
        public:
			virtual const String entityclass() const override;
			virtual void entityclass(const String & entityclass) override;
			virtual const String attribute() const override;
			virtual void attribute(const String & attribute) override;
			virtual const uint64_t id() const override;
			virtual void id(const uint64_t & id) override;

            virtual String buildCreateEntityClassQuery() = 0;
            virtual String buildRelationEntityClassQuery(const String& t1,
                                                         const String& t2) = 0;
            virtual String buildIDSelectQuery() = 0;
            virtual String buildSingleAttributeSelectQuery() = 0;
            virtual String buildSingleValueInsertQuery(const String& attribute) = 0;
            virtual String buildIdInsertQuery(std::map<String, String>&) = 0;

			/*
			 * implemented methods
			 */
            virtual String startTransaction() override;
            virtual String commitTransaction() override;
            virtual String rollbackTransaction() override;
            virtual String buildSingleValueSelectQuery() override;
			virtual String buildDeleteEntityClassQuery(bool ifExists = false) override;
            virtual String buildAddAttributeQuery(const String& defaultValue,
                                                  const String& type,
                                                  const int16_t size) override;
		protected:
			virtual String replaceASCnDESC(ORDER o);
			virtual String replaceType(const String& type) = 0;
		private:
			String _entityclass;
			String _attribute;
			uint64_t _id;
        };
    }
}

#endif //LIB_TOCDB_ABSTRACTQUERYBUILDER

