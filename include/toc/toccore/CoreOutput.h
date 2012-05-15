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

#ifndef LIB_TOCCORE_COREOUTPUT
#define LIB_TOCCORE_COREOUTPUT 1

#include <toc/tocstring/TocString.h>

#include <toc/boost/extension/impl/decl.hpp>
#ifndef DLL_TOC_CORE
#ifdef MAKE_TOC_CORE
#define DLL_TOC_CORE BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_CORE BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace TOC
{
    namespace core
    {
        class CoreOutput
        {
        public:
            virtual ~CoreOutput(){};
            
            virtual CoreOutput& operator<<(const String& str) = 0;
            virtual CoreOutput& operator<<(const Char* str) = 0;
            virtual CoreOutput& endline() = 0;
            
            virtual CoreOutput& flush() = 0;
            
            DLL_TOC_CORE CoreOutput& operator<<( void (*funcPointer)(CoreOutput&) );
        };
        
        // Modificationfunctions
        
        extern void DLL_TOC_CORE endline(CoreOutput&);
        extern void DLL_TOC_CORE flush(CoreOutput&);
        
        // StandartOutput
        
        class DLL_TOC_CORE StdOutput : public CoreOutput
        {
        public:
            CoreOutput& operator<<(const String& str);
            CoreOutput& operator<<(const Char* str);
            CoreOutput& endline();
            
            CoreOutput& flush();
        };
        
        extern StdOutput DLL_TOC_CORE stdOutput;
    }
}

#endif //LIB_TOCCORE_COREOUTPUT
