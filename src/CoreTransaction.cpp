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

#include <boost/foreach.hpp>
#include <toc/tocdb/CoreTransaction.h>
#include <toc/tocdb/DataPatch.h>
#include <toc/tocdb/DB.h>

namespace TOC
{
	namespace DB
	{
		void
		transactionCleanupFunction(CoreTransaction*)
		{}
		
		boost::thread_specific_ptr<CoreTransaction>
		CoreTransaction::
		tsp(&transactionCleanupFunction);
		
		CoreTransaction::
		CoreTransaction()
		{
			if (tsp.get() != NULL)
				throw TransactionAlreadyExistsException();
			tsp.reset(this);
		}
		
		CoreTransaction::
		~CoreTransaction()
		{
			if (tsp.get() == NULL)
				throw BrokenTransactionContextException();
			tsp.release();
		}
		
		bool
		CoreTransaction::
		isThereAContext()
		{
			return tsp.get() != NULL;
		}
		
		void
		CoreTransaction::
		addDataPatch(AbstractDataPatch* p)
		{
			if (!isThereAContext())
				throw NoTransactionException();
			tsp.get()->queue.push(p);
		}
		
		void
		CoreTransaction::
		save()
		{
			DB::Instance().createTransaction();
			while (!queue.empty())
			{
				AbstractDataPatch* patch = queue.front();
				patch->save();
				queue.pop();
				delete patch;
			}
			DB::Instance().commit();
		}
	}
}
