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

#include <boost/noncopyable.hpp>
#include <toc/boost/extension/extension.hpp>
#include <toc/tocdb/AbstractQueryBuilder.h>
#include <toc/tocdb/StandardTypes.h>

namespace TOC
{
    namespace DB
    {
        class BOOST_EXTENSION_EXPORT_DECL MySQLQueryBuilder : public AbstractQueryBuilder, boost::noncopyable
        {
        public:
            //transactions, locks, etc...
            String startTransaction();
            String commitTransaction();
            String rollbackTransaction();
            
            String buildIdInsertQuery(std::map<String, String>&);
            String buildRelationEntityClassQuery(const String&,
                                                 const String&);
            String buildCreateEntityClassQuery();
            String buildAddAttributeQuery(const String& defaultValue,
                                          const String& _type,
                                          const int16_t size);
            String buildSingleAttributeSelectQuery();
            
            // selects
            String buildIDSelectQuery();
            String buildSingleValueSelectQuery();
            
            // inserts
            String buildSingleValueInsertQuery(const String&);

			const uint64_t id() const;
			void id(const uint64_t&);

			const String attribute() const;
			void attribute(const String&);

			const String entityclass() const;
			void entityclass(const String&);

			static AbstractQueryBuilder* newQueryBuilder();
        private:
            template<class T>
            void buildOrderPart(T& ss);
            template<class T>
            void buildWherePart(T& ss);

			uint64_t _id;
			String  _attribute;
			String  _entityclass;
        };
    }
}
