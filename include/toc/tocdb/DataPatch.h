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
#ifndef LIB_TOCDB_DATAPATCH
#define LIB_TOCDB_DATAPATCH 1

#include <map>

#include <toc/tocstring/TocString.h>

namespace TOC
{
	namespace DB
	{
		class AbstractDataPatch
		{
		public:
			virtual
			void
			save() = 0;
			
			virtual
			~AbstractDataPatch();
		};
		
		class SingleValuePatch : AbstractDataPatch
		{
		public:
			SingleValuePatch(const std::string& table,
			                 uint64_t row,
			                 const std::string& att,
			                 const std::string& value);
			
			std::string
			table;
			
			uint64_t
			row;
			
			std::string
			att;
			
			std::string
			value;
			
			void save();
		};
		
		class SingleRowPatch : public AbstractDataPatch
		{
		public:
			typedef std::map<std::string,
			                 std::string>
			        Map;
			
			SingleRowPatch(const std::string& table,
						   const Map&);
			
			void
			save();
			
		private:
			std::string table;
			Map m;
		};
	}
}

#endif //LIB_TOCDB_DATAPATCH

