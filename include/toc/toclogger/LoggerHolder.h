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

#ifndef LIB_TOC_LOGGER_LOGGERHOLDER
#define LIB_TOC_LOGGER_LOGGERHOLDER 1

#include <boost/any.hpp>
#include <map>
#include <toc/toclogger/macros/loggerMacros.h>
#include <toc/tocstring.h>

namespace TOC
{
	using boost::any;

	class TocLoggerHolder
	{
	public:

		TOC_LOGGER_TEMPLATE_ARG(A, B, C, D, Logger)
		static
		void
		registerLogger(Logger<A, B, C, D>& logger);

		/*TOC_LOGGER_TEMPLATE_ARG_NAME_FIRST(Name, A, B, C, Logger)
		static
		Logger<A, B, C, Name>&
		getLogger();*/

	private:
		static
		std::map<std::string, any>
		loggers;
	};

	TOC_LOGGER_TEMPLATE_ARG(A, B, C, Name, Logger)
	void
	TocLoggerHolder::
	registerLogger(Logger<A, B, C, Name>& logger)
	{
		loggers[Name] = logger;
	}

/*	TOC_LOGGER_TEMPLATE_ARG_NAME_FIRST(Name, A, B, C, Logger)
	Logger<A, B, C, Name>&
	TocLoggerHolder::
	getLogger()
	{
		return loggers[Name];
	}*/
}

#endif //LIB_TOC_LOGGER_LOGGERHOLDER

