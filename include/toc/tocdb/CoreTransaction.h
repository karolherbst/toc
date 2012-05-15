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
/*
 * CoreTransaction
 *
 * only model modified in transactioncontext will be stored to database.
 * create a CoreTransaction context at the beginning of your function
 * and make sure no other transaction is created after that.
 */

#ifndef LIB_TOCCORE_CORETRANSACTION
#define LIB_TOCCORE_CORETRANSACTION 1

#include <boost/thread/tss.hpp>
#include <queue>
#include <toc/tocexception/CoreException.h>

#include <toc/boost/extension/impl/decl.hpp>
#ifndef DLL_TOC_DB
#ifdef MAKE_TOC_DB
#define DLL_TOC_DB BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_DB BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace TOC
{
    namespace DB
    {
        COREEXCEPTION_SUBCLASS(TransactionException,
                               CSTRING("critical failure occured within transaction"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(TransactionException,
                                          TransactionAlreadyExistsException,
                                          CSTRING("a Transaction already exists in this context!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(TransactionException,
                                          BrokenTransactionContextException,
                                          CSTRING("this transaction context is broken!"));
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(TransactionException,
                                          NoTransactionException,
                                          CSTRING("there wasn't a valid transaction context!"));
        struct AbstractDataPatch;
        
        class DLL_TOC_DB CoreTransaction
        {
        public:
            CoreTransaction();
            ~CoreTransaction();
            
            void save();
            void static addDataPatch(AbstractDataPatch*);
            
            bool static isThereAContext();
            
        private:
            static boost::thread_specific_ptr<CoreTransaction> tsp;
            
            std::queue<AbstractDataPatch*> queue;
        };
    }
}

#endif //SERVER_CORE_CORETRANSACTION
