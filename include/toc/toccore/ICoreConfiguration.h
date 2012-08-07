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

#ifndef LIB_TOCCORE_INTERFACE_CONFIGURATION
#define LIB_TOCCORE_INTERFACE_CONFIGURATION 1

#include <toc/toccore/Interface.h>
#include <toc/tocstring/TocString.h>

// interface macros

namespace TOC
{
	namespace core
	{
		class ICoreConfiguration
		{
			virtual 
			void
			load(const std::string& filename) = 0;

			virtual
			void
			save(const std::string& filename) = 0;

			virtual 
			void
			cliConfiguration(){};

			virtual 
			~ICoreConfiguration(){};
		};
	}
}

#endif //LIB_TOCCORE_INTERFACE_CONFIGURATION

