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

#include <toc/tocdb/DBCol.h>

#include <toc/tocdb/AbstractQueryBuilder.h>
#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBValue.h>

namespace TOC
{
	namespace DB
	{
		DBCol::
		DBCol(const String& col,
		      AbstractQueryBuilder& _qb)
		:	qb(_qb)
		{
			qb.attribute(col);
		}
		
		DBValue
		DBCol::
		operator[](uint64_t id)
		{
			qb.id(id);
			return DBValue(qb);
		}
		
		DBCol&
		DBCol::
		create(const String& defaultValue,
		       const String& type,
		       const int16_t size)
		{
			DB::Instance().executeQuery(qb.buildAddAttributeQuery(defaultValue,
			                                                      type,
			                                                      size));
			return *this;
		}
		
		DBCol&
		DBCol::
		operator>>(std::vector<String>& vec)
		{
			DB::Instance().executeSingleColQuery(qb.buildSingleAttributeSelectQuery(),
			                                     vec);
			return *this;
		}
		
		uint64_t
		DBCol::
		search(const String& value)
		{
			String result;
			qb.addWherePair(qb.attribute(),
			                value);
			DB::Instance().executeSingleValueQuery(qb.buildIDSelectQuery(),
			                                       result);
			return boost::lexical_cast<uint64_t>(result);
		}
		
		DBCol&
		DBCol::
		where(const String& att,
		      const String value)
		{
			qb.addWherePair(att, value);
			return *this;
		}
		
		DBCol&
		DBCol::
		order(const String& att,
		      ORDER order)
		{
			qb.addOrderPair(att, order);
			return *this;
		}
	}
}
