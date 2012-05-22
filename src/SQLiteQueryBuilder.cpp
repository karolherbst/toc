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

#include "SQLiteQueryBuilder.h"

namespace TOC
{
	namespace DB
	{
		String
		SQLiteQueryBuilder::
		buildCreateEntityClassQuery()
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildSingleAttributeSelectQuery()
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildIDSelectQuery()
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildIdInsertQuery(std::map<String, String>&)
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildRelationEntityClassQuery(const String&,
		                                     const String&)
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildAddAttributeQuery(const String& defaultValue,
		                              const String& _type,
		                              const int16_t size)
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildSingleValueSelectQuery()
		{
			
		}

		String
		SQLiteQueryBuilder::
		buildSingleValueInsertQuery(const String&)
		{
			
		}

		String
		SQLiteQueryBuilder::
		startTransaction()
		{
			
		}

		String
		SQLiteQueryBuilder::
		commitTransaction()
		{
			
		}

		String
		SQLiteQueryBuilder::
		rollbackTransaction()
		{
			
		}

		const uint64_t
		SQLiteQueryBuilder::
		id() const
		{
			
		}

		void
		SQLiteQueryBuilder::
		id(const uint64_t&)
		{
			
		}

		const String
		SQLiteQueryBuilder::
		attribute() const
		{
			
		}

		void
		SQLiteQueryBuilder::
		attribute(const String&)
		{
			
		}

		const String
		SQLiteQueryBuilder::
		entityclass() const
		{
			
		}

		void
		SQLiteQueryBuilder::
		entityclass(const String&)
		{
			
		}
		
		AbstractQueryBuilder*
		SQLiteQueryBuilder::
		newQueryBuilder()
		{
			return new SQLiteQueryBuilder();
		}
	}
}
