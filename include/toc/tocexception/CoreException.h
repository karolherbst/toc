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

#ifndef LIB_TOCCORE_COREEXCEPTION
#define LIB_TOCCORE_COREEXCEPTION 1

#include <exception>
#include <toc/boost/extension/impl/decl.hpp>
#include <toc/tocstring/TocString.h>

#ifndef DLL_TOC_EXCEPTION
#ifdef MAKE_TOC_EXCEPTION
#define DLL_TOC_EXCEPTION BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_EXCEPTION BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace TOC
{
    namespace core
    {
        /**
         * little Exception class providing a constructor for string arguments
         *
         * @class   CoreException
         * @author  Karol Herbst
         * @since   0.1
         */
        class DLL_TOC_EXCEPTION CoreException : public std::exception
        {
        public:
            /**
             * default constructor
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            CoreException() throw();
            
            /**
             * string class based constructor
             *
             * @author  Karol Herbst
             * @since   0.1
             * @param   message the message for the new created exception
             */
            CoreException(String message) throw();
            
            /**
             * default destructor
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual ~CoreException() throw() override;
            
            /**
             * method to return error message
             *
             * @author  Karol Herbst
             * @since   0.1
             * @return  message from this exception
             */
            virtual const char* what() const throw() override;

			const String getMessage() const;
		protected:
			String name;

        private:
            const String message;
        };
    }
}

/**
 * this macro provides a simple was to subclass from CoreException
 *
 * @author  Karol Herbst
 * @since   0.1
 * @param   classname   the name of the new exception class
 * @param   string      default error message
 */
#define COREEXCEPTION_SUBCLASS(classname, string) SUBCLASS_OF_COREXCEPTION_SUBCLASS(TOC::core::CoreException, classname, string)

/**
 * this macro provides a simple way to subclass a CoreException subclass
 *
 * @author  Karol Herbst
 * @since   0.1
 * @param   parentclass the parent exception classname
 * @param   childclass  the new exception class name
 * @param  str         the default message
 */
#define SUBCLASS_OF_COREXCEPTION_SUBCLASS(parentclass, childclass, str) \
struct childclass : public parentclass                                  \
{                                                                       \
    childclass(String message)                                          \
    :   parentclass(message){this->name = #childclass;}                 \
    childclass()                                                        \
    :   childclass(str){}                                               \
}

#endif //LIB_TOCCORE_COREEXCEPTION
