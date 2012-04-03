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

#ifndef LIB_TOCLOGGER_LOGGER
#define LIB_TOCLOGGER_LOGGER 1

#include <string>

#include <TocEnv/TocEnv.h>
#include <toc/toclogger/macros/loggerMacros.h>

namespace TOC
{
    /**
     * several logging levels
     *
     * @author  Karol Herbst
     * @since   0.1
     */
    SCOPED_ENUM( LOGGINGTYPE, uint16_t )
    {
        ERROR = 0,
        WARN = 1,
        INFO = 2,
        DEBUG = 3
    };

    extern std::string LOG_STRINGS[4];

    CREATE_LOGGER_NAME_CLASS(DEFAULTNAME, "Default");

    #define TEMPLATE_CLASS_DEF template <class Task, template <class> class Processor, template<const char*> class Appender, const char* LoggerInfo>
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
         * @param   str         the input string
         * @return  TOC::TocLogger
         */
        template <LOGGINGTYPE,
                  typename StringType>
        inline TocLogger TEMPLATE_CLASS_ARG & log(StringType str);

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
        enables[ SCOPED_ENUM_VALUE(LOGGINGTYPE, ERROR) ] = error;
        enables[ SCOPED_ENUM_VALUE(LOGGINGTYPE, WARN) ] = warn;
        enables[ SCOPED_ENUM_VALUE(LOGGINGTYPE, INFO) ] = info;
        enables[ SCOPED_ENUM_VALUE(LOGGINGTYPE, DEBUG) ] = debug;
    }

    TEMPLATE_CLASS_DEF
    template<LOGGINGTYPE type,
             typename StringType>
    TocLogger TEMPLATE_CLASS_ARG &
    TocLogger TEMPLATE_CLASS_ARG::
    log( StringType str )
    {
        if ( enables[type] ) processor.add( appender.createOutputString( str, LOG_STRINGS[type] ) );
        return *this;
    }

    #undef TEMPLATE_CLASS_DEF
    #undef TEMPLATE_CLASS_ARG
};

#endif //LIB_TOCLOGGER_LOGGER