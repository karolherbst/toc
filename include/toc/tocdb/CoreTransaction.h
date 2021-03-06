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

#include <queue>

#include <boost/thread/tss.hpp>

#include <toc/tocexception/CoreException.h>

namespace TOC
{
	namespace DB
	{
		COREEXCEPTION_SUBCLASS(TransactionException,
		                       "critical failure occured within transaction");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(TransactionException,
		                                   TransactionAlreadyExistsException,
		                                   "a Transaction already exists in this context!");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(TransactionException,
		                                   BrokenTransactionContextException,
		                                   "this transaction context is broken!");
		
		SUBCLASS_OF_COREEXCEPTION_SUBCLASS(TransactionException,
		                                   NoTransactionException,
		                                   "there wasn't a valid transaction context!");
		
		class AbstractDataPatch;
		
		class CoreTransaction
		{
		public:
			CoreTransaction();
			
			~CoreTransaction();
			
			void
			save();
			
			static
			void 
			addDataPatch(AbstractDataPatch*);
			
			static
			bool
			isThereAContext();
			
		private:
			static
			boost::thread_specific_ptr<CoreTransaction>
			tsp;
			
			std::queue<AbstractDataPatch*>
			queue;
		};
	}
}

#endif //SERVER_CORE_CORETRANSACTION

