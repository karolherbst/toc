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

#include <toc/tocdb/DataPatch.h>
#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBCol.h>
#include <toc/tocdb/DBTable.h>
#include <toc/tocdb/DBValue.h>

namespace TOC
{
	namespace DB
	{
		AbstractDataPatch::
		~AbstractDataPatch()
		{}
		
		SingleValuePatch::
		SingleValuePatch(const String& _table,
		                 uint64_t _row,
		                 const String& _att,
		                 const String& _value)
		:	table(_table),
		row(_row),
		att(_att),
		value(_value){}
		
		void
		SingleValuePatch::
		save()
		{
			DB::Instance()[table][att][row] = value;
		}
		
		SingleRowPatch::
		SingleRowPatch(const String& _table,
		               const Map& _m)
		:   table(_table),
		m(_m)
		{}
		
		void
		SingleRowPatch::
		save()
		{
			DB::Instance()[table].insert(m);
		}
	}
}
