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
		class SQLiteQueryBuilder : public AbstractSQLQueryBuilder
		{
		public:
			virtual String buildCreateEntityClassQuery() override;
			virtual String buildSingleAttributeSelectQuery() override;
			virtual String buildIDSelectQuery() override;
			virtual String buildIdInsertQuery(std::map<String, String>&) override;
			virtual String buildRelationEntityClassQuery(const String&,
			                                             const String&) override;
			virtual String buildSingleValueInsertQuery(const String&) override;

			virtual String startTransaction() override;

			virtual const uint64_t id() const override;
			virtual void id(const uint64_t&) override;

			virtual const String attribute() const override;
			virtual void attribute(const String&) override;

			virtual const String entityclass() const override;
			virtual void entityclass(const String&) override;

			static AbstractQueryBuilder* newQueryBuilder();
		protected:
			virtual String replaceType(const String& type) override;
		private:
			String _entityclass;
			String _attribute;
			uint64_t _id;
		};
	}
}

