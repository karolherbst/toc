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

#include <boost/algorithm/string/trim.hpp>
#include <toc/toccore/CoreInput.h>
#include <toc/toccore/TocCommandManager.h>

namespace TOC
{
	namespace core
	{
		TocCommandManager
		commandManager;
		
		TocCommandManager::
		TocCommandManager()
		:	input(stdInput),
			output(stdOutput){}
		
		void
		TocCommandManager::
		requestCommandToSession(Session_Core* session,
		                        std::string command)
		{
			session->write(command);
		}
		
		void
		TocCommandManager::
		requestCommand(std::string command)
		{
			// delete all spaces at the front and back
			trim(command);
			
			// we wanna connect to a channel
			if (command.operator[](0) == '/')
			{
				std::string channelName = command.substr(0,
				                                         command.find(' '));
				erase_first(command,
				            channelName);
				trim(command);
				
				if (setActualChannel(channelName.substr(1)))
					if (command.size() <= 0)
						output << "New Channel selected: "
						       << channelName.substr(1)
						       << endline;
					else
						requestCommandToSession(actualChannel,
						                        command);
				else
					output << "such a channel doesnt exist"
					       << endline;
			}
			else
				if (actualChannel)
					requestCommandToSession(actualChannel,
					                        command);
				else
					output << "no channel selected"
					       << endline;
		}
		
		void
		TocCommandManager::
		openCommandInput()
		{
			char line[512];
			
			while (input.getline(line,
			                     512))
				requestCommand(line);
		}
		
		void
		TocCommandManager::
		registerChannel(Session_Core* session,
		                std::string str)
		{
			channels.insert(std::pair<std::string,
			                          Session_Core*>(str,
			                                         session));
		}
		
		bool
		TocCommandManager::
		setActualChannel(std::string channel)
		{
			if(channels[channel])
			{
				actualChannel = channels[channel];
				return true;
			}
			return false;
		}
	}
}
