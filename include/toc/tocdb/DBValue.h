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

#ifndef LIB_TOCDB_DB_DBVALUE
#define LIB_TOCDB_DB_DBVALUE 1

#include <toc/tocstring/TocString.h>

namespace TOC
{
	namespace DB
	{
		class AbstractQueryBuilder;
		
		class DBValue
		{
		public:
			DBValue(AbstractQueryBuilder&);
			
			DBValue&
			operator=(const std::string& value);
			
			friend std::ostream&
			operator<<(std::ostream& ostr,
			           const DBValue& m);
		private:
			std::string
			convert() const;
			
			AbstractQueryBuilder&
			qb;
		};		
	}
}

#endif //LIB_TOCDB_DB_DBVALUE

