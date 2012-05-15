#ifndef LIB_TOCMODULE_TOCMODULE
#define LIB_TOCMODULE_TOCMODULE 1

#include <toc/boost/extension/extension.hpp>
#include <toc/boost/extension/factory_map.hpp>
#include <toc/toccore/Interface.h>
#include <toc/toccore/Version.h>
#include <queue>

#include <toc/boost/extension/impl/decl.hpp>
#ifndef DLL_TOC_MODULE
#ifdef MAKE_TOC_MODULE
#define DLL_TOC_MODULE BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_MODULE BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace TOC
{
    namespace core
    {
        interface DLL_TOC_MODULE TocModule
        {
            ABSTRACT (Version currentVersion() const);
            ABSTRACT (Version latestFullPackageVersion() const);
            ABSTRACT (Version buildForServerVersion() const);
            ABSTRACT (void loadDataForVersion(IVersion&) const);
            
            GENERIC (~TocModule());
        };
    }
}

#endif //LIB_TOCMODULE_TOCMODULE
