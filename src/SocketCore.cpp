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

#include <toc/toccore/SocketCore.h>

#include <boost/foreach.hpp>
#include <boost/thread.hpp>

namespace TOC
{
	namespace core
	{
		SocketCore::
		SocketCore()
		:   thread(NULL)
		{
			instances.insert(this);
		}
		
		SocketCore::
		~SocketCore()
		{
			instances.erase(this);
		}
		
		std::set<SocketCore*>
		SocketCore::
		instances;
		
		void
		SocketCore::
		stop()
		{
			thread->interrupt();
		}
		
		void
		SocketCore::
		join()
		{
			thread->join();
		}
		
		void
		SocketCore::
		stopAll()
		{
			BOOST_FOREACH(SocketCore* socket,
			              instances)
			socket->stop();
		}
	}
}
