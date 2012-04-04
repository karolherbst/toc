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

#include <toc/toccore/CoreOutput.h>

#include <iostream>

namespace TOC
{
    namespace core
    {
        CoreOutput& CoreOutput::operator<<( void (*funcPointer)(CoreOutput&) )
        {
            funcPointer(*this);
            return *this;
        }
        
        // Modificationfunctions
        
        void endline(CoreOutput& output)
        {
            output.endline().flush();
        }
        
        extern void flush(CoreOutput& output)
        {
            output.flush();
        }
        
        // StandartOutput
        
        CoreOutput& StdOutput::operator<<(const String& str)
        {
            std::cout << str;
            return *this;
        }
        
        CoreOutput& StdOutput::operator<<(const char* str)
        {
            std::cout << str;
            return *this;
        }
        
        CoreOutput& StdOutput::endline()
        {
            std::cout << std::endl;
            return *this;
        }
        
        CoreOutput& StdOutput::flush()
        {
            std::cout.flush();
            return *this;
        }
        
        StdOutput stdOutput;
    }
}
