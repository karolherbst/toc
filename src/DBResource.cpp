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

#include <toc/tocdb/DBResource.h>

#include <toc/boost/extension/shared_library.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>

#include <toc/tocdb/DBDriver.h>
#include <toc/tocdb/DBExceptions.h>

//MySQL Driver
#include "MySQLDriver.h"
#include "MySQLQueryBuilder.h"
//SQLite Driver
#include "SQLiteDriver.h"
#include "SQLiteQueryBuilder.h"

namespace TOC
{
	namespace DB
	{
		DBResourceImpl::
		DBResourceImpl()
		{
			registerDriver(CSTRING("MySQL"),
			               &MySQLDriver::newDriver,
			               &MySQLQueryBuilder::newQueryBuilder);
			registerDriver(CSTRING("SQLite"),
			               &SQLiteDriver::newDriver,
			               &SQLiteQueryBuilder::newQueryBuilder);
		}

		DBDriver*
		DBResourceImpl::
		newDriver() const
		{
			return loadedDrivers.at(_pd)._dbdriverBuilderFunc();
		}

		AbstractQueryBuilder*
		DBResourceImpl::
		newQueryBuilder() const
		{
			return loadedDrivers.at(_pd)._abstractQueryBuilderFunc();
		}

		std::list<String>
		DBResourceImpl::
		availableDrivers() const
		{
			std::list<String> result;

			BOOST_FOREACH(const DriverPair &p, loadedDrivers)
			{
				result.push_back(p.first);
			}

			return result;
		}

		DBResourceImpl::DriverEntry::
		DriverEntry(shared_library* dl,
		            function<DBDriver* (void)> dbdriverBuilderFunc,
		            function<AbstractQueryBuilder* (void)> abstractQueryBuilderFunc)
		:	_dl(dl),
			_dbdriverBuilderFunc(dbdriverBuilderFunc),
			_abstractQueryBuilderFunc(abstractQueryBuilderFunc){}

		DBResourceImpl::DriverEntry::
		~DriverEntry()
		{
			// todo: unload driver
		}
	}
}
