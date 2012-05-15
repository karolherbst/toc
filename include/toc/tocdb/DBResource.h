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

#include <toc/boost/extension/impl/decl.hpp>
#include <toc/boost/extension/shared_library.hpp>
#include <boost/function/function_fwd.hpp>
#include <list>
#include <map>
#include <toc/tocdb/DBExceptions.h>
#include <toc/tocstring.h>

#ifndef DLL_TOC_DB
#ifdef MAKE_TOC_DB
#define DLL_TOC_DB BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_DB BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace TOC
{
    namespace DB
    {
		class AbstractQueryBuilder;
		class DBDriver;

        using boost::extensions::shared_library;
        using boost::function;

        class DLL_TOC_DB DBResource
        {
        public:
            template <typename ST>
            static void registerDriver(const ST &name,
                                       function<DBDriver * (void)>,
                                       function<AbstractQueryBuilder * (void)>);

            template <typename ST1, typename ST2>
            static void registerDriver(const ST1 &name,
			                           const ST2 &path);

			template <typename ST>
            static void preferedDriver(const ST&);
            static String preferedDriver();

            static std::list<String> availableDrivers();

			template <typename ST>
			static bool isLoaded(const ST&);

			template <typename ST>
			static bool isBuiltIn(const ST&);

            static DBDriver * newDriver();
            static AbstractQueryBuilder * newQueryBuilder();

        private:
			static String _pd;

			struct DriverEntry
			{
				shared_library *_dl;
				function<DBDriver * (void)> _dbdriverBuilderFunc;
				function<AbstractQueryBuilder * (void)> _abstractQueryBuilderFunc;

				DriverEntry(shared_library *,
				            function<DBDriver * (void)>,
				            function<AbstractQueryBuilder * (void)>);
				~DriverEntry();

			};
			typedef std::pair<String, DriverEntry> DriverPair;
			static std::map<String, DriverEntry> loadedDrivers;
        };

		template <typename ST>
		void
		DBResource::
		registerDriver(const ST &name,
		               function<DBDriver * (void)> d_func,
		               function<AbstractQueryBuilder * (void)> qb_func)
		{
			loadedDrivers.insert(DriverPair(name,
			                                DriverEntry(nullptr,
			                                            d_func,
			                                            qb_func)
			                               )
			                    );
		}

		template <typename ST1, typename ST2>
		void
		DBResource::
		registerDriver(const ST1 &name,
		               const ST2 &path)
		{
			shared_library *lib = new shared_library(path, true);

			if (!lib->open())
			{
				delete lib;
				throw DriverLibNotValid();
			}

			function<DBDriver * (void)> d_func = lib->get<DBDriver *>("newDriver");
			function<AbstractQueryBuilder * (void)> qb_func = lib->get<AbstractQueryBuilder *>("newQueryBuilder");

			if (!d_func || !qb_func)
			{
				delete lib;
				throw DriverLibNotValid();
			}

			loadedDrivers.insert(DriverPair(name,
			                                DriverEntry(lib,
			                                            d_func,
			                                            qb_func)
			                               )
			                    );
		}

		template <typename ST>
		void
		DBResource::
		preferedDriver(const ST &name)
		{
			if (isLoaded(name))
				_pd = name;
			else throw DriverNotLoaded();
		}

		template <typename ST>
		bool
		DBResource::
		isLoaded(const ST &name)
		{
			return loadedDrivers.count(name) != 0;
		}

		template <typename ST>
		bool
		DBResource::
		isBuiltIn(const ST &name)
		{
			return isLoaded(name) && loadedDrivers.at(name)._dl == nullptr;
		}
    }
}
