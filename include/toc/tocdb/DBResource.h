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

#include <boost/extension/impl/decl.hpp>
#include <boost/function/function_fwd.hpp>

#ifndef DLL_TOC_DB
#ifdef MAKE_TOC_DB
#define DLL_TOC_DB BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_DB BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace boost
{
    namespace extensions
    {
        class shared_library;
    }
}

namespace TOC
{
    namespace DB
    {
        class AbstractQueryBuilder;
        class DBDriver;
        
        class DLL_TOC_DB DBResource
        {
        public:
            static void setDL(boost::extensions::shared_library*);
            static DBDriver* newDriver();
            // move into driver
            static AbstractQueryBuilder* newQueryBuilder();
            
        private:
            static boost::extensions::shared_library* dl;
            static boost::function<DBDriver* (void)> dbdriverBuilderFunc;
            static boost::function<AbstractQueryBuilder* (void)> abstractQueryBuilderFunc;
        };
    }
}
