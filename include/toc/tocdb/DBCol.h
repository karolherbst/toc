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

#ifndef LIB_TOCDB_DB_DBCOL
#define LIB_TOCDB_DB_DBCOL 1

#include <vector>

#include <toc/tocdb/DBTypes.h>
#include <toc/tocdb/StandardTypes.h>
#include <toc/tocstring/TocString.h>

namespace TOC
{
	namespace DB
	{
		class AbstractQueryBuilder;
		class DBValue;
		
		class DBCol
		{
		public:
			DBCol(const std::string& col,
			      AbstractQueryBuilder&);
			
			DBValue
			operator[](uint64_t id);
			
			DBCol&
			create(const std::string& defaultValue = NULLSTRING,
			       const std::string& type = DBString,
			       const int16_t size = 10);
			
			// query building
			DBCol&
			where(const std::string& att,
			      const std::string value);
			
			DBCol&
			order(const std::string& att,
			      ORDER order);
			
			// search over value
			uint64_t
			search(const std::string& value);
			
			// store values in vec
			DBCol&
			operator>>(std::vector<std::string>& vec);
			
		private:
			std::string
			orderAtt;
			
			ORDER
			orderKind;
			
			AbstractQueryBuilder&
			qb;
		};
	}
}

#endif //LIB_TOCDB_DB_DBCOL

