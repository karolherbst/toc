/*
 *  CoreException.cpp
 *  Projekt
 *
 *  Created by Karol Herbst on 31.01.11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <toc/tocexception/CoreException.h>
#include <cstring>

namespace TOC
{
    namespace core
    {
        static const std::string DEFAULT_ERRPR_STRING = "A critical Failure occured!\0";

        CoreException::CoreException() throw()
        :   message(DEFAULT_ERRPR_STRING)
        {

        }

        CoreException::CoreException(std::string _message) throw()
        :   message(_message)
        {

        }

        CoreException::~CoreException() throw()
        {

        }

        const char* CoreException::what() const throw()
        {
            return message.c_str();
        }
    }
}
