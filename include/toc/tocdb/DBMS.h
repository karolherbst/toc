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

#ifndef LIB_TOCDB_DBMS
#define LIB_TOCDB_DBMS 1

#include <toc/tocstring.h>

namespace TOC
{
	namespace DB
	{
		namespace DBMS
		{
			extern
			const std::string
			DB2;
			
			extern
			const std::string
			MariaDB;
			
			extern
			const std::string
			MongoDB;
			
			extern
			const std::string
			MySQL;
			
			extern
			const std::string
			Oracle;
			
			extern
			const std::string
			PostgreSQL;
			
			extern
			const std::string
			SQLite;
		}
	}
}

#endif //LIB_TOCDB_DBMS

