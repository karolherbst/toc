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

#include <toc/tocstring/TocString.h>

/**
 * create a new class for logging
 *
 * @author  Karol Herbst
 * @since   0.1
 * @param   typenamename of the class, use sth like defaltLog
 * @param   str printed name
 */
#define CREATE_LOGGER_NAME_CLASS_DEF(name) extern const char name []
#define CREATE_LOGGER_NAME_CLASS_IMPL(name, str) extern "C" const char name [sizeof(str)] = str
#define CREATE_LOGGER(name, nameClass) TOC::TocLogger<WriteToConsole, SingleThreadedProcessor, SimpleAppender, nameClass> name

#define TOC_LOGGER_TEMPLATE_ARG(a, b, c, d, e) \
template <typename a, \
          template <typename> class b, \
          template <const char*> class c, \
          const char* d, \
          template <typename, \
                    template <typename> class, \
                    template <const char*> class, \
                    const char*> \
          class e>

#define TOC_LOGGER_TEMPLATE_ARG_NAME_FIRST(a, b, c, d, e) \
template <typename b, \
          template <typename> class c, \
          template <const char*> class d, \
          const char* a, \
          template <typename, \
                    template <typename> class, \
                    template <const Char*> class, \
                    const char*> \
          class e>

