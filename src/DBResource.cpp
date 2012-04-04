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

#include <boost/extension/shared_library.hpp>
#include <boost/function.hpp>

#include <toc/tocdb/DBExceptions.h>

namespace TOC
{
    namespace DB
    {
        void
        DBResource::
        setDL(boost::extensions::shared_library* _dl)
        {
            if (dl != NULL)
                throw std::exception();
            dl = _dl;
            
            if (!dl->open())
                throw CantLoadDriverLib();
            abstractQueryBuilderFunc = dl->get<AbstractQueryBuilder*>("newQueryBuilder");
            dbdriverBuilderFunc = dl->get<DBDriver*>("newDriver");
            
            if(!abstractQueryBuilderFunc || !dbdriverBuilderFunc)
                throw DriverLibNotValid();
        }
        
        DBDriver*
        DBResource::
        newDriver()
        {
            return dbdriverBuilderFunc();
        }
        
        AbstractQueryBuilder*
        DBResource::
        newQueryBuilder()
        {
            return abstractQueryBuilderFunc();
        }
        
        boost::extensions::shared_library*
        DBResource::
        dl = NULL;
        
        boost::function<DBDriver* (void)>
        DBResource::
        dbdriverBuilderFunc = NULL;
        
        boost::function<AbstractQueryBuilder* (void)>
        DBResource::
        abstractQueryBuilderFunc = NULL;
    }
}
