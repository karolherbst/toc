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
#include <string>

typedef std::string String;

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
void storeArgumentsIn(const std::string& str,
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
std::string
getStringUntilChar(const std::string& str,
                   const char c);

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
std::string
getStringAfterChar(const std::string& str,
                   const char c,
                   std::string::size_type s = 0);

template <class C>
void storeArgumentsIn(const std::string& str,
                      C& c)
{
    std::string _tmp = str;
    trim(_tmp);
    
    c.push_back(getStringUntilChar(_tmp, ' '));
    
    if (str.find(' ') == std::string::npos)
        return;
    
    _tmp = getStringAfterChar(_tmp, ' ') + ' '; // tweak
    
    while (_tmp.size() > 0)
    {
        if (_tmp == " ")
            return;
        
        char searchFor = ' ';
        trim_left(_tmp);
        
        if (_tmp.operator[](0) == '"')
            searchFor = '"';
        
        if (searchFor == ' ')
        {
            std::string foundString = getStringUntilChar(_tmp,
                                                         searchFor);
            c.push_back(foundString);
            _tmp = getStringAfterChar(_tmp,
                                      searchFor);
        }
        else
        {
            std::string foundString = getStringUntilChar(getStringAfterChar(_tmp,
                                                                            searchFor),
                                                    searchFor);
            c.push_back(foundString);
            _tmp = getStringAfterChar(getStringAfterChar(_tmp,
                                                         searchFor),
                                      searchFor);
        }
    }
}

#endif //LIB_TOC_STRING
