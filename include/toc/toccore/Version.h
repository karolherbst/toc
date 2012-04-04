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

#ifndef LIB_TOCCORE_VERSION
#define LIB_TOCCORE_VERSION 1

#include <stdint.h>
#include <boost/operators.hpp>
#include <toc/toccore/Interface.h>
#include <toc/toccore/Macros.h>

#include <boost/extension/impl/decl.hpp>
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
        interface DLL_TOC_CORE IVersion : public boost::totally_ordered<IVersion>
        {
            ABSTRACT(uint16_t rel());
            ABSTRACT(uint16_t maj());
            ABSTRACT(uint16_t min());
            ABSTRACT(uint16_t bui());
            ABSTRACT(void rel(uint16_t));
            ABSTRACT(void maj(uint16_t));
            ABSTRACT(void min(uint16_t));
            ABSTRACT(void bui(uint16_t));
            ABSTRACT(IVersion& operator++(int i));
            ABSTRACT(IVersion& operator--(int d));
            
            bool operator<(const IVersion&) const;
            bool operator==(const IVersion&) const;
            void operator=(const uint16_t[4]);
        };
        
        std::ostream &
        operator<<(std::ostream &ostr,
                   TOC::core::IVersion &v);
        
        class DLL_TOC_CORE Version : public IVersion
        {
            uint16_t _rel;
            uint16_t _maj;
            uint16_t _min;
            uint16_t _bui;
        public:
            Version(uint16_t rel,
                    uint16_t maj,
                    uint16_t min,
                    uint16_t bui);
            Version(const uint16_t[4]);
            
            GETTERSETTER (uint16_t, _rel, rel)
            GETTERSETTER (uint16_t, _maj, maj)
            GETTERSETTER (uint16_t, _min, min)
            GETTERSETTER (uint16_t, _bui, bui)
            
            IVersion& operator++(int i);
            IVersion& operator--(int d);
        };
    }
}

#endif //LIB_TOCCORE_VERSION
