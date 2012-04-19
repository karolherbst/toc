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

#ifndef LIB_TOC_LOGGER_LOGGER
#define LIB_TOC_LOGGER_LOGGER 1

#include <toc/toclogger/macros/loggerMacros.h>
#include <toc/tocstring/TocString.h>

namespace TOC
{
	/**
	 * several logging levels
	 *
	 * @author  Karol Herbst
	 * @since   0.1
	 */
	enum class LOGGINGTYPE : uint16_t
	{
		ERROR = 0,
		WARN = 1,
		INFO = 2,
		DEBUG = 3
	};
	
	extern String LOG_STRINGS[4];
	
	#define TEMPLATE_CLASS_DEF template <class Task, template <class> class Processor, template<const Char*> class Appender, const Char* LoggerInfo>
	#define TEMPLATE_CLASS_ARG <Task, Processor, Appender, LoggerInfo>
	
	/**
	 * simple logging class
	 *
	 * @class   TocLogger
	 * @author  Karol Herbst
	 * @since   0.1
	 */
	TEMPLATE_CLASS_DEF
	class TocLogger
	{
	public:
		/**
		 * log a simple string to the logger
		 *
		 * @author  Karol Herbst
		 * @since   0.1
		 * @tparam  LOGGINGTYPE level of logging
		 * @param   str		 the input string
		 * @return  TOC::TocLogger
		 */
		template <LOGGINGTYPE, typename StringType>
		inline TocLogger TEMPLATE_CLASS_ARG &
		log(StringType str);
		
		/**
		 * constructor with booleans for activating logger levels
		 *
		 * @author  Karol Herbst
		 * @since   0.1
		 * @param   error
		 * @param   warn
		 * @param   info
		 * @param   debug
		 * @return  TOC::TocLogger
		 */
		TocLogger(bool error,
		          bool warn,
		          bool info,
		          bool debug);

		/**
		 * default constructor
		 *
		 * switches will be global
		 */
		TocLogger();

	private:
		Appender<LoggerInfo> appender;
		Processor<Task> processor;
		bool enables[4];
	};

	TEMPLATE_CLASS_DEF
	TocLogger TEMPLATE_CLASS_ARG::
	TocLogger(bool error,
	          bool warn,
	          bool info,
	          bool debug)
	{
		enables[ (uint16_t) LOGGINGTYPE::ERROR ] = error;
		enables[ (uint16_t) LOGGINGTYPE::WARN ] = warn;
		enables[ (uint16_t) LOGGINGTYPE::INFO ] = info;
		enables[ (uint16_t) LOGGINGTYPE::DEBUG ] = debug;
	}

	TEMPLATE_CLASS_DEF
	TocLogger TEMPLATE_CLASS_ARG::
	TocLogger()
	:	enables( {true,
		          true,
		          true,
		          true} ){}

	TEMPLATE_CLASS_DEF
	template<LOGGINGTYPE type, typename StringType>
	TocLogger TEMPLATE_CLASS_ARG &
	TocLogger TEMPLATE_CLASS_ARG::
	log( StringType str )
	{
		if ( enables[ (uint16_t) type] ) processor.add( appender.createOutputString( str,
		LOG_STRINGS[ (uint16_t) type] ) );
		return *this;
	}

	#undef TEMPLATE_CLASS_DEF
	#undef TEMPLATE_CLASS_ARG
};

#endif //LIB_TOC_LOGGER_LOGGER
