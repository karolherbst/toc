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

#ifndef LIB_TOCCORE_VERSION
#define LIB_TOCCORE_VERSION 1

#include <stdint.h>
#include <boost/operators.hpp>
#include <toc/toccore/Interface.h>
#include <toc/toccore/Macros.h>
#include <toc/tocstring/TocString.h>

namespace TOC
{
	namespace core
	{
		class IVersion : public boost::totally_ordered<IVersion>
		{
		public:
			virtual
			uint16_t
			rel() = 0;
			
			virtual
			uint16_t
			maj() = 0;
			
			virtual
			uint16_t
			min() = 0;
			
			virtual
			uint16_t
			bui() = 0;
			
			virtual
			void
			rel(uint16_t) = 0;
			
			virtual
			void
			maj(uint16_t) = 0;
			
			virtual
			void
			min(uint16_t) = 0;
			
			virtual
			void
			bui(uint16_t) = 0;
			
			virtual
			IVersion&
			operator++(int i) = 0;
			
			virtual
			IVersion&
			operator--(int d) = 0;
			
			bool
			operator<(const IVersion&) const;
			
			bool
			operator==(const IVersion&) const;
			
			void
			operator=(const uint16_t[4]);
		};
		
		std::ostream&
		operator<<(std::ostream& ostr,
		           IVersion& v);
		
		class Version : public IVersion
		{
		private:
			uint16_t
			_rel;
			
			uint16_t
			_maj;
			
			uint16_t
			_min;
			
			uint16_t
			_bui;

		public:
			Version(uint16_t rel,
			        uint16_t maj,
			        uint16_t min,
			        uint16_t bui);

			Version(const uint16_t[4]);

			GETTERSETTER(uint16_t, _rel, rel)
			GETTERSETTER(uint16_t, _maj, maj)
			GETTERSETTER(uint16_t, _min, min)
			GETTERSETTER(uint16_t, _bui, bui)

			IVersion&
			operator++(int i) override;

			IVersion&
			operator--(int d) override;
		};
	}
}

#endif //LIB_TOCCORE_VERSION

