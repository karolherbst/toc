/**
 * @file
 *
 * @author  Karol Herbst
 * @since   0.1
 *
 * @section LICENSE
 *
 * @section DESCRIPTION
 */

#ifndef LIB_TOCCORE_COREEXCEPTION
#define LIB_TOCCORE_COREEXCEPTION 1

#include <exception>
#include <string>

#include <boost/extension/impl/decl.hpp>
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
            CoreException(std::string message) throw();
            
            /**
             * default destructor
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            ~CoreException() throw();
            
            /**
             * method to return error message
             *
             * @author  Karol Herbst
             * @since   0.1
             * @return  message from this exception
             */
            const char* what() const throw();
            
        private:
            const std::string message;
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
#define COREEXCEPTION_SUBCLASS(classname, String) SUBCLASS_OF_COREXCEPTION_SUBCLASS(TOC::core::CoreException, classname, string)

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
    childclass()                                                        \
    :   parentclass(str){}                                              \
    childclass(std::string message)                                     \
    :   parentclass(message){}                                          \
}

#endif //LIB_TOCCORE_COREEXCEPTION
