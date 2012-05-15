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

#ifndef LIB_TOCCORE_COREINPUT
#define LIB_TOCCORE_COREINPUT 1

#include <toc/tocstring/TocString.h>

namespace TOC
{
    namespace core
    {
        class CoreInput
        {
        public:
            virtual ~CoreInput();
            virtual bool getline(Char*, int32_t) = 0;
        };
        
        class StdInput : public CoreInput
        {
        public:
            bool getline(Char*, int32_t);
        };
        
        extern StdInput stdInput;
    }
}

#endif //LIB_TOCCORE_COREINPUT