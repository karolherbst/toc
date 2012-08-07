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

#ifndef LIB_TOCCORE_SESSIONCORE
#define LIB_TOCCORE_SESSIONCORE 1

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <toc/toccore/CoreOutput.h>
#include <toc/toclogger.h>
#include <toc/tocmessage/ChatMessage.h>
#include <deque>
#include <set>

#include <toc/boost/extension/impl/decl.hpp>
#ifndef DLL_TOC_CORE
#ifdef MAKE_TOC_CORE
#define DLL_TOC_CORE BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_CORE BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

CREATE_LOGGER_NAME_CLASS_DEF(SessionLog);

namespace TOC
{
	using message::ChatMessage;
	namespace core
	{
		typedef std::deque<ChatMessage> MessageQueue;

		class DLL_TOC_CORE Session_Core
		{
		private:
			MessageQueue messageQueue;
			CREATE_LOGGER(logger, SessionLog);

			void
			do_write(ChatMessage&);

			void
			handleWrite(const boost::system::error_code&);

			boost::asio::io_service& io_service_;

			virtual
			std::set<Session_Core*>&
			getSetOfOtherSessions() = 0;

			void commandLoop(char* buffer,
			                 const boost::system::error_code&,
			                 size_t bytes_transferred);

			template <typename Method,
			          typename Object>
			void
			asyncReadHeaderWrapper(char* buffer,
			                       Object*,
			                       Method,
			                       const boost::system::error_code&,
			                       size_t bytes_transferred);

			template <typename Method, typename Object>
			void asyncReadBodyWrapper(char* buffer,
			                          Object*,
			                          Method,
			                          const boost::system::error_code&,
			                          size_t bytes_transferred);

			bool isInCommandLoop;

			std::map<std::string,
			         std::string>
			_values;

		protected:
			void
			do_close();

			// for Servers
			Session_Core(boost::asio::io_service& io_service,
			             CoreOutput& output);

			enum _TMP_CONSTANTS
			{
				max_length = 512
			};

			boost::asio::ip::tcp::socket
			socket_;

			void
			makePublic();

			void
			unmakePublic();

			void
			disconnect();

			virtual
			void
			atDisconnect() = 0;

			virtual
			void
			requestCommand(const ChatMessage&) = 0;

			CoreOutput&
			output;

			template <typename Clazz,
			          typename Method>
			void
			asyncRead(Method method);

		public:
			// for Client
			Session_Core(boost::asio::io_service&,
			             boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
			             CoreOutput&);

			virtual
			~Session_Core();

			void
			handle_connect(const boost::system::error_code&,
			               boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

			// for Client end
			virtual
			void
			start() = 0;

			void
			close();

			boost::asio::ip::tcp::socket&
			socket();

			void
			writeToAll(const char* msg,
			           uint16_t length);

			void
			writeToAll(const std::string&);

			void
			writeToAll(const ChatMessage&);

			void
			writeToAllExceptThis(const char* msg,
			                     uint16_t length,
			                     Session_Core* _this);

			void
			writeToAllExceptThis(const std::string&,
			                     Session_Core* _this);

			void
			writeToAllExceptThis(const ChatMessage&,
			                     Session_Core* _this);

			void
			write(const char* msg,
			      uint16_t length);

			void
			write(const std::string&);

			void
			write(const ChatMessage&);

			Session_Core&
			operator<<(const std::string&);

			Session_Core&
			operator<<(const ChatMessage&);

			void
			enterCommandLoop();

			std::string&
			operator[](std::string& key);
		};

		template <typename M,
		          typename O>
		void
		Session_Core::
		asyncReadHeaderWrapper(char* buffer,
		                       O*,
		                       M method,
		                       const boost::system::error_code&,
		                       size_t /*bytes_transferred*/)
		{
			uint32_t size = ChatMessage::timestampLength
			              + ChatMessage::bodyLengthFromHeader(buffer);

			socket_.async_receive(boost::asio::buffer(&buffer[ChatMessage::headerLength],
			                                          size),
			                      boost::bind(&Session_Core::asyncReadBodyWrapper<M, O>,
			                                  this,
			                                  buffer,
			                                  static_cast<O*>(this),
			                                  method,
			                                  boost::asio::placeholders::error,
			                                  boost::asio::placeholders::bytes_transferred));
		}

		template <typename Method,
		          typename Object>
		void
		Session_Core::
		asyncReadBodyWrapper(char* buffer,
		                     Object* object,
		                     Method method,
		                     const boost::system::error_code& error,
		                     size_t bytes_transferred)
		{
			boost::bind(method,
			            object,
			            buffer,
			            error,
			            bytes_transferred)();
			delete[] buffer;
		}

		template <typename Clazz,
		          typename Method>
		void
		Session_Core::
		asyncRead(Method method)
		{
			// optimize allocation of buffer
			// should we use 2 buffers?
			char* buffer = new char[max_length];
			socket_.async_receive(boost::asio::buffer(buffer,
			                      ChatMessage::headerLength),
			                      boost::bind(&Session_Core::asyncReadHeaderWrapper<Method,
			                                                                        Clazz>,
			                                  this,
			                                  buffer,
			                                  static_cast<Clazz*>(this),
			                                  method,
			                                  boost::asio::placeholders::error,
			                                  boost::asio::placeholders::bytes_transferred));
		}
	}
}

#endif //LIB_TOCCORE_SESSIONCORE

