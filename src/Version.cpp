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

#include <toc/toccore/Version.h>

namespace TOC
{
	namespace core
	{
		bool
		IVersion::
		operator<(const IVersion& __v) const
		{
			IVersion& right = const_cast<IVersion&>(__v);
			IVersion& left = const_cast<IVersion&>(*this);
			
			if (left.rel() < right.rel())
				return true;
			if (left.rel() == right.rel())
			{
				if (left.maj() < right.maj())
					return true;
				if (left.maj() == right.maj())
				{
					if (left.min() < right.min())
						return true;
					if (left.min() == right.min())
					{
						if (left.bui() < right.bui())
							return true;
					}
				}
			}
			return false;
		}
		
		bool
		IVersion::
		operator==(const IVersion& __v) const
		{
			IVersion& right = const_cast<IVersion&>(__v);
			IVersion& left = const_cast<IVersion&>(*this);
			
			return right.rel() == left.rel()
			    && right.maj() == left.rel()
			    && right.min() == left.min()
			    && right.bui() == left.bui(); 
		}
		
		void
		IVersion::
		operator=(const uint16_t arr[4])
		{
			rel(arr[0]);
			maj(arr[1]);
			min(arr[2]);
			bui(arr[3]);
		}
		
		std::ostream&
		operator<<(std::ostream& ostr,
		           TOC::core::IVersion& v)
		{
			return (ostr << lexical_cast<std::string>(v.rel()) << '.'
			             << lexical_cast<std::string>(v.maj()) << '.'
			             << lexical_cast<std::string>(v.min()) << ':'
			             << lexical_cast<std::string>(v.bui()));
		}
		
		Version::
		Version(uint16_t rel,
		        uint16_t maj,
		        uint16_t min,
		        uint16_t bui)
		:	_rel(rel),
			_maj(maj),
			_min(min),
			_bui(bui){}
		
		Version::
		Version(const uint16_t arr[4])
		:	Version(arr[0],
			        arr[1],
			        arr[2],
			        arr[3]){}
		
		IVersion&
		Version::
		operator++(int i)
		{
			return *this;
		}
		
		IVersion&
		Version::
		operator--(int d)
		{
			return *this;
		}
	}
}

