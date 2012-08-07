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

#ifndef LIB_TOC_MESSAGE_CHATINFORMATION
#define LIB_TOC_MESSAGE_CHATINFORMATION 1

#include <TocEnv/TocEnv.h>

namespace TOC
{
	namespace message
	{
		/**
		 * encoded commands for in protocol activities
		 *
		 * @author  Karol Herbst
		 * @since   0.1
		 */
		enum class SystemActions : uint16_t
		{
			/**
			 * this command is used to ask the server which port a given
			 * service has.
			 *
			 * client only command
			 *
			 * request has 1 argument:
			 *  -# char array name of the service, NULL terminated
			 *
			 * response has 2 arguments:
			 *  -# as request
			 *  -# port of requested service, 16bit
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			PORTOF = 0x0001,
			
			/**
			 * this command tells the other side the own binary version
			 *
			 * has 4 arguments
			 *  -# release part, 8bit
			 *  -# major part, 8bit
			 *  -# minor part, 8bit
			 *  -# build part, 32bit
			 */
			VERSION = 0x0002,
			
			/**
			 * client only
			 *
			 * request has no arguments
			 *
			 * response has 3 arguments
			 *  -# algorithm string, NULL terminated
			 *  -# strength, in most cases the bit value, 32bit
			 *  -# public key, terminated by header informations
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			PUBKEY = 0x0003
		};
		
		/**
		 * encoded commands for account activities
		 *
		 * @author  Karol Herbst
		 * @since   0.1
		 */
		enum class AccountAction : uint16_t
		{
			/**
			 * client only
			 *
			 * request only
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			LOGOUT = 0x0001,
			
			/**
			 * simple login command
			 *
			 * client only
			 *
			 * request has 2 arguments
			 *  -# account name, NULL terminated
			 *  -# encrypted password, NULL terminated
			 *
			 * response has 1 argument
			 *  -# boolean, true if successfully
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			LOGIN = 0x0002,
			
			/**
			 * simple IM command
			 *
			 * request only
			 *
			 * hast 2 arguments
			 *  -# destination as char-array, NULL terminated
			 *  -# message as char-array, NULL terminated
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			SAYTO = 0x0003,
			
			/**
			 * account creation
			 *
			 * client only
			 *
			 * request has 3 arguments
			 *  -# account name, NULL terminated
			 *  -# password, NULL terminated
			 *  -# email, NULL terminated
			 *
			 * response has 2 argument
			 *  -# boolean, true if everything alright
			 *  -# error message, NULL terminated, only if 1 == false
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			CREATE = 0x0004,
			
			/**
			 * transfer a simple list of acc names
			 *
			 * client only
			 *
			 * request has no arguments
			 *
			 * response has 1 argument
			 *  -# comma seperated list of names, NULL terminated
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			LIST = 0x0005
		};
		
		/**
		 * command for in server command line interface
		 *
		 * @author  Karol Herbst
		 * @since   0.1
		 */
		enum class CLIActions : uint16_t
		{
			/**
			 * used to shutdown the server
			 *
			 * has no arguments
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			SHUTDOWN = 0x0001
		};
		
		/**
		 * general commands fo error handling and other stuff
		 *
		 * do not use this command, use subcommands with the commands above
		 *
		 * all subcommands are response only
		 *
		 * @author  Karol Herbst
		 * @since   0.1
		 */
		enum class GENERELANSWERS : uint16_t
		{ // please count backwards
			/**
			 * is sent, if a subcommand is not found
			 *
			 * has 1 argument
			 *  -# the sent subcommand
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			SUBCOMMAND_NOT_FOUND = 0xffff,
			/**
			 * is sent, if the argcount was wrong
			 *
			 * has 1 argument
			 *  -# the sent subcommand
			 *
			 * @author  Karol Herbst
			 * @since   0.1
			 */
			WRONG_ARG_COUNT = 0xfffe
		};
	}
}

#endif //LIB_TOC_MESSAGE_CHATINFORMATION

