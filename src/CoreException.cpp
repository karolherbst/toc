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

#include <toc/tocexception/CoreException.h>

namespace TOC
{
	namespace core
	{
		static const String DEFAULT_ERROR_STRING = CSTRING("A critical Failure occured!");

		CoreException::
		CoreException() throw()
		:	CoreException(DEFAULT_ERROR_STRING)
		{}

		CoreException::
		CoreException(String _message) throw()
		:	name("CoreException"),
			message(_message)
		{}

		CoreException::
		~CoreException() throw()
		{}

		const char*
		CoreException::
		what() const throw()
		{
			return static_cast<const char*>(this->getMessage().c_str());
		}

		const String
		CoreException::
		getMessage() const
		{
			return this->name + ": " + this->message;
		}
	}
}
