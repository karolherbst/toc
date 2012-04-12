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

#ifndef LIB_TOCLOGGER_SIMPLEAPPENDER
#define LIB_TOCLOGGER_SIMPLEAPPENDER 1

#include <toc/tocstring/TocString.h>

namespace TOC
{
    template <const Char* Name>
    class SimpleAppender
    {
    public:
        template <typename StringType, typename StringType2>
        String
        createOutputString(StringType str, StringType2 level);
    };

    template <const Char* Name>
    template <typename StringType, typename StringType2>
    String
    SimpleAppender<Name>::
    createOutputString(StringType str, StringType2 level)
    {
        StringStream ss;
        ss << '<' << level << "> (" << Name << "): " << str;
        return ss.str();;
    }
}

#endif //LIB_TOCLOGGER_SIMPLEAPPENDER
