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
                               CSTRING("critical DB failure"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(DBException,
                                          CantLoadDriverLib,
                                          CSTRING("failed to load driver lib!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(DBException,
                                          DriverLibNotValid,
                                          CSTRING("the driver lib isn't valid!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(DBException,
                                          CantConnectToDBException,
                                          CSTRING("can't connect to db!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(DBException,
                                          AuthenticationFailedException,
                                          CSTRING("authentication failed!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(DBException,
                                          QueryException,
                                          CSTRING("Query failed!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(DBException,
                                          EmptyResultException,
                                          CSTRING("The Result is empty!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(DBException,
                                          QueryFailedException,
                                          CSTRING("The query failed!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(DBException,
                                          TableDoesntExistException,
                                          CSTRING("The query failed!"));
    }
}

#endif //LIB_TOCDB_DBEXCEPTIONS
