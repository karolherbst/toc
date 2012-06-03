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

#include <toc/boost/extension/extension.hpp>
#include <toc/tocdb/AbstractSQLQueryBuilder.h>
#include <toc/tocdb/StandardTypes.h>

namespace TOC
{
    namespace DB
    {
        class BOOST_EXTENSION_EXPORT_DECL MySQLQueryBuilder : public AbstractSQLQueryBuilder
        {
        public:
            String buildIdInsertQuery(std::map<String, String>&);
            String buildRelationEntityClassQuery(const String&,
                                                 const String&);
            String buildCreateEntityClassQuery();
            String buildSingleAttributeSelectQuery();
            
            // selects
            String buildIDSelectQuery();
            
            // inserts
            String buildSingleValueInsertQuery(const String&);

			static AbstractQueryBuilder* newQueryBuilder();
		protected:
			virtual String replaceType(const String& type) override;
        private:
            template<class T>
            void buildOrderPart(T& ss);
            template<class T>
            void buildWherePart(T& ss);
        };
    }
}
