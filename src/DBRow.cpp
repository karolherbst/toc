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

#include <toc/tocdb/DBRow.h>

#include <toc/tocdb/AbstractQueryBuilder.h>
#include <toc/tocdb/DBValue.h>
#include <toc/tocstring/TocString.h>

namespace TOC
{
	namespace DB
	{
		DBRow::
		DBRow(uint64_t _id,
		      AbstractQueryBuilder& _qb)
		:	qb(_qb)
		{
			qb.id(_id);
		}
		
		DBValue
		DBRow::
		operator[](const String& att)
		{
			qb.attribute(att);
			return DBValue(qb);
		}
	}
}