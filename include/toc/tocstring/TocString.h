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

#ifndef LIB_TOC_STRING
#define LIB_TOC_STRING 1

// we use the standard string implementation
#include <iostream>
#include <string>
#include <sstream>

#define USE_UNICODE 0

#if USE_UNICODE
	#define COUT              	std::wcout
	#define CIN               	std::wcin
	#define CSTRING(s)        	L##s
	#define CCHAR(c)          	L##c

	typedef std::wstring      	String;
	typedef wchar_t	          	Char;
	typedef std::wostream     	OStream;
	typedef std::wstringstream	StringStream;
#else
	#define COUT              	std::cout
	#define CIN               	std::cin
	#define CSTRING(str)      	str
	#define CCHAR(c)          	c

	typedef std::string       	String;
	typedef char              	Char;
	typedef std::ostream      	OStream;
	typedef std::stringstream 	StringStream;
#endif

// lexical cast should be used overall
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

// string algos from boost
#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

/**
 * this function split the space seperatet String into substring stored in the
 * given container
 *
 * @author  Karol Herbst
 * @since   0.1
 * @param   str the space seperated String
 * @param   c   the container
 */
template <class C>
void storeArgumentsIn(const String& str,
                      C& c);

/**
 * this function returns a substring til the given char
 *
 * @author  Karol Herbst
 * @since   0.1
 * @return  String
 * @param   str the input string
 * @param   c   the char to seperate str
 */
String
getStringUntilChar(const String& str,
                   const Char c);

/**
 * this function returns a substring after the given char
 *
 * @author  Karol Herbst
 * @since   0.1
 * @return  String
 * @param   str the input string
 * @param   c   the char to seperate str
 * @param   s   the size to start
 */
String
getStringAfterChar(const String& str,
                   const Char c,
                   String::size_type s = 0);

template <class C>
std::ostream&
operator<<(std::ostream &,
		   const std::list<C> &);

template <class C>
void storeArgumentsIn(const String& str,
                      C& c)
{
	String _tmp = str;
	trim(_tmp);
	
	c.push_back(getStringUntilChar(_tmp, CCHAR(' ')));
	
	if (str.find(CCHAR(' ')) == String::npos)
		return;
	
	_tmp = getStringAfterChar(_tmp, CCHAR(' ')) + CCHAR(' '); // tweak
	
	while (_tmp.size() > 0)
	{
		if (_tmp == CSTRING(" "))
			return;
		
		Char searchFor = CCHAR(' ');
		trim_left(_tmp);
		
		if (_tmp.operator[](0) == CCHAR('"'))
			searchFor = CCHAR('"');
		
		if (searchFor == CCHAR(' '))
		{
			String foundString = getStringUntilChar(_tmp,
			                                        searchFor);
			c.push_back(foundString);
			_tmp = getStringAfterChar(_tmp,
			                          searchFor);
		}
		else
		{
			String foundString = getStringUntilChar(getStringAfterChar(_tmp,
			                                                           searchFor),
			                                        searchFor);
			c.push_back(foundString);
			_tmp = getStringAfterChar(getStringAfterChar(_tmp,
			                                             searchFor),
			                          searchFor);
		}
	}
}

template <class C>
std::ostream&
operator<<(std::ostream & os,
           const std::list<C> &list)
{
	os << "List<";
	if (list.begin() != list.end())
		os << *list.begin();
	std::for_each(++list.begin(),
	              list.end(),
	              [&os](const C &e)
	              {
	              	os << ", " << e;
	              });
	return os << '>';
}

#endif //LIB_TOC_STRING
