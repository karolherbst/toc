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

#ifndef LIB_TOCCORE_DISPATCHER
#define LIB_TOCCORE_DISPATCHER 1

#include <stdint.h>

#include <boost/bind.hpp>

namespace TOC
{
	namespace core
	{
		template <typename Class,
		          typename ArgType>
		class Dispatcher
		{
		public:
			Dispatcher();
			typedef void (Class::*FuncPointer)(ArgType*);

		protected:
			void
			addFuncPointer(FuncPointer,
			               uint8_t);

			void
			dispatch(uint16_t,
			         ArgType*);

		private:
			FuncPointer* methods;
		};

		template <class C,
		          class A>
		Dispatcher<C, A>::
		Dispatcher()
		:	methods(new FuncPointer[1]){}

		template <typename C,
		          typename A>
		void
		Dispatcher<C, A>::
		addFuncPointer(FuncPointer func,
		               uint8_t index)
		{
			static size_t size = 1;
			if (index >= size)
			{
				size *= 2;
				methods = (FuncPointer*) realloc(methods,
				                                 size * sizeof(func));
			}
			methods[index] = func;
		}

		template <typename C,
		          typename A>
		void
		Dispatcher<C, A>::
		dispatch(uint16_t index,
		         A* arg)
		{
			boost::bind(methods[index],
			            static_cast<C*>(this),
			            arg)();
		}
	}
}

#endif //LIB_TOCCORE_DISPATCHER

