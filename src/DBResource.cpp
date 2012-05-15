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

/*
 * TODO
 *
 * cstring should be static members
 *
 */

#include <toc/tocdb/DBResource.h>

#include <toc/boost/extension/shared_library.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>

#include <toc/tocdb/DBExceptions.h>

namespace TOC
{
	namespace DB
	{
		String
		DBResource::
		_pd;

		std::map<String, DBResource::DriverEntry>
		DBResource::
		loadedDrivers;

		DBDriver*
		DBResource::
		newDriver()
		{
			return loadedDrivers.at(_pd)._dbdriverBuilderFunc();
		}

		AbstractQueryBuilder*
		DBResource::
		newQueryBuilder()
		{
			return loadedDrivers.at(_pd)._abstractQueryBuilderFunc();
		}

		std::list<String>
		DBResource::
		availableDrivers()
		{
			std::list<String> result;

			BOOST_FOREACH(const DriverPair &p, loadedDrivers)
			{
				result.push_back(p.first);
			}

			return result;
		}

		DBResource::DriverEntry::
		DriverEntry(shared_library* dl,
		            function<DBDriver* (void)> dbdriverBuilderFunc,
		            function<AbstractQueryBuilder* (void)> abstractQueryBuilderFunc)
		:	_dl(dl),
			_dbdriverBuilderFunc(dbdriverBuilderFunc),
			_abstractQueryBuilderFunc(abstractQueryBuilderFunc){}

		DBResource::DriverEntry::
		~DriverEntry()
		{
			// todo: unload driver
		}
	}
}
