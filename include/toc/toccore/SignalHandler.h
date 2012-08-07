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

#ifndef LIB_TOCCORE_SIGNALHANDLER
#define LIB_TOCCORE_SIGNALHANDLER 1

#include <iostream>
#include <csignal>
#include <boost/bind.hpp>
#include <loki/Singleton.h>

namespace TOC
{
	namespace core
	{
		class SignalHandlerImpl
		{
		public:
			template <int Signal>
			void
			registerHandler(void (*)(int));

		private:
			template <int Signal,
			          typename Handler>
			void
			handlerWrapper(Handler handler);
		};

		typedef Loki::SingletonHolder<SignalHandlerImpl> SignalHandler;
		#define signalHandler SignalHandler::Instance()

		template <int Signal>
		void
		SignalHandlerImpl::registerHandler(void (*handler)(int))
		{
			signal(Signal,
			       handler);
		}

		template <int Signal,
		          typename Handler>
		void
		SignalHandlerImpl::handlerWrapper(Handler handler)
		{
			handler(Signal);
		}
	}
}

#endif //LIB_TOCCORE_SIGNALHANDLER

