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
			virtual
			std::string
			buildCreateEntityClassQuery() override;
			
			virtual
			std::string
			buildSingleAttributeSelectQuery() override;
			
			virtual
			std::string
			buildIdInsertQuery(std::map<std::string,
			                            std::string>&) override;
			
			virtual
			std::string
			buildRelationEntityClassQuery(const std::string&,
			                              const std::string&) override;
			
			virtual
			std::string
			buildSingleValueInsertQuery(const std::string&) override;

			virtual
			std::string
			startTransaction() override;

			static AbstractQueryBuilder* newQueryBuilder();
			
		protected:
			virtual
			std::string
			replaceType(const std::string& type) override;
		};
	}
}

