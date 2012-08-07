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

#include <toc/tocdb/AbstractQueryBuilder.h>
#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBValue.h>

namespace TOC
{
	namespace DB
	{
		DBValue::
		DBValue(AbstractQueryBuilder& _qb)
		:	qb(_qb)
		{}
		
		std::string
		DBValue::
		convert() const
		{
			std::string result;
			DB::Instance().executeSingleValueQuery(qb.buildSingleValueSelectQuery(),
			                                       result);
			return result;
		}
		
		DBValue&
		DBValue::
		operator=(const std::string& value)
		{
			DB::Instance().executeQuery(qb.buildSingleValueInsertQuery(value));
			return *this;
		}
		
		std::ostream&
		operator<<(std::ostream& ostr,
		           const DBValue& m)
		{
			return ostr << m.convert();
		}
	}
}

