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

#ifndef LIB_TOCDB_DBEXCEPTIONS
#define LIB_TOCDB_DBEXCEPTIONS 1

#include <toc/tocexception/CoreException.h>

namespace TOC
{
	namespace DB
	{
		COREEXCEPTION_SUBCLASS(DBException,
		                       "critical DB failure");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   CantLoadDriverLib,
		                                   "failed to load driver lib!");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   DriverNotLoaded,
		                                   "the given driver is not loaded");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   DriverLibNotValid,
		                                   "the driver lib isn't valid!");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   CantConnectToDBException,
		                                   "can't connect to db!");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   AuthenticationFailedException,
		                                   "authentication failed!");

		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   CantCloseDBException,
		                                   "unable to close database");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   MalformedQueryException,
		                                   "Query was malformed!");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   QueryWasMissUsedException,
		                                   "the given query was execute at the wrong place!!");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   EmptyResultException,
		                                   "The Result is empty!");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(DBException,
		                                   TableDoesntExistException,
		                                   "The query failed!");
    }
}

#endif //LIB_TOCDB_DBEXCEPTIONS

