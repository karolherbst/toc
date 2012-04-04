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

#ifndef LIB_TOCDB_STANDARTTYPES
#define LIB_TOCDB_STANDARTTYPES 1

#include <toc/tocstring/TocString.h>
#include <boost/lexical_cast.hpp>

#include <boost/extension/impl/decl.hpp>
#ifndef DLL_TOC_DB
#ifdef MAKE_TOC_DB
#define DLL_TOC_DB BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_DB BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

#define createAttType(classname) \
struct DLL_TOC_DB classname \
{ \
static const String name; \
static const String type; \
static const String defaultValue; \
static const uint16_t size; \
}

#define createAttTypeSymbols(classname, _name, _type, _default, _size) \
const String classname::name = _name; \
const String classname::type = _type; \
const String classname::defaultValue = boost::lexical_cast<String>(_default); \
const uint16_t classname::size = _size

#define createListTypeSymbols(parentclass, childclass) \
namespace TOC{ namespace DB{ \
template<> String TOC::DB::ListAtt<parentclass, childclass>::name = ""; \
template<> String TOC::DB::ListAtt<parentclass, childclass>::type = ""; \
template<> String TOC::DB::ListAtt<parentclass, childclass>::defaultValue = ""; \
template<> uint16_t TOC::DB::ListAtt<parentclass, childclass>::size = 0; \
}}

#define setListTypes(parentclass, childclass, _name, _size) \
TOC::DB::ListAtt<parentclass, childclass>::name = _name; \
TOC::DB::ListAtt<parentclass, childclass>::type = TOC::DBInt; \
TOC::DB::ListAtt<parentclass, childclass>::defaultValue = "0"; \
TOC::DB::ListAtt<parentclass, childclass>::size = _size

extern const String DLL_TOC_DB NULLSTRING;
class DLL_TOC_DB NULLTYPE{};

namespace TOC
{
    namespace DB
    {
        template <typename Parent, typename Child>
        struct ListAtt
        {
            static String name;
            static String type;
            static String defaultValue;
            static uint16_t size;
        };
    }
    
    /// DBTypes:
    extern const String DLL_TOC_DB DBString;
    extern const String DLL_TOC_DB DBInt;
    extern const String DLL_TOC_DB DBFloat;
    extern const String DLL_TOC_DB DBText;
    
    createAttType(NameAtt);
    createAttType(MailAtt);
    createAttType(PasswordAtt);
    createAttType(SessionTypeAtt);
    createAttType(ArgCountAtt);
    createAttType(ArgAtt);
    createAttType(ActionAtt);
    createAttType(MajVersionAtt);
    createAttType(MinVersionAtt);
    createAttType(RelVersionAtt);
    createAttType(BuildVersionAtt);
    createAttType(TextAtt);
}

#endif //LIB_TOCDB_STANDARTTYPES
