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
 
 add a check server ready funtionality
 => latency + wait for ready
 */

#include <toc/toccore/SessionCore.h>
#include <boost/bind.hpp>


namespace TOC
{
    namespace core
    {
        using boost::asio::ip::tcp;
        
        // implement return code for last message
        Session_Core::Session_Core(boost::asio::io_service& io_service,
                                   CoreOutput& _output)
        :   io_service_(io_service),
        isInCommandLoop(false),
        socket_(io_service),
        output(_output)
        {
            
        }
        
        Session_Core::~Session_Core()
        {
            
        }
        
        Session_Core::Session_Core(boost::asio::io_service& io_service,
                                   tcp::resolver::iterator endpoint_iterator,
                                   CoreOutput& _output)
        :   io_service_(io_service),
        isInCommandLoop(false),
        socket_(io_service),
        output(_output)
        {
            tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint,
                                  boost::bind(&Session_Core::handle_connect,
                                              this,
                                              boost::asio::placeholders::error,
                                              ++endpoint_iterator));
        }
        
        void Session_Core::handle_connect(const boost::system::error_code& error,
                                          tcp::resolver::iterator endpoint_iterator)
        {
            if (!error)
            {
                start();
            }
            else if (endpoint_iterator != tcp::resolver::iterator())
            {
                socket_.close();
                tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint,
                                      boost::bind(&Session_Core::handle_connect,
                                                  this,
                                                  boost::asio::placeholders::error,
                                                  ++endpoint_iterator));
            }
        }
        
        void Session_Core::makePublic()
        {
            getSetOfOtherSessions().insert(this);
        }
        
        void Session_Core::unmakePublic()
        {
            getSetOfOtherSessions().erase(this);
        }
        
        tcp::socket& Session_Core::socket()
        {
            return socket_;
        }
        
        void Session_Core::writeToAll(const Char* msg, uint16_t length)
        {
            writeToAllExceptThis(msg, length, 0);
        }
        
        void Session_Core::writeToAll(const String& msg)
        {
            writeToAllExceptThis(msg, 0);
        }
        
        void Session_Core::writeToAll(const ChatMessage& msg)
        {
            writeToAllExceptThis(msg, 0);
        }
        
        void Session_Core::writeToAllExceptThis(const Char* msg, uint16_t length, Session_Core* _this)
        {
            for (std::set<Session_Core*>::iterator it = getSetOfOtherSessions().begin(); it != getSetOfOtherSessions().end(); it++)
            {
                if (*it != _this)
                    (*it)->write(msg, length);
            }
        }
        
        void Session_Core::writeToAllExceptThis(const String& msg, Session_Core* _this)
        {
            for (std::set<Session_Core*>::iterator it = getSetOfOtherSessions().begin(); it != getSetOfOtherSessions().end(); it++)
            {
                if (*it != _this)
                    (*it)->write(msg);
            }
        }
        
        void Session_Core::writeToAllExceptThis(const ChatMessage& msg, Session_Core* _this)
        {
            for (std::set<Session_Core*>::iterator it = getSetOfOtherSessions().begin(); it != getSetOfOtherSessions().end(); it++)
            {
                if (*it != _this)
                    (*it)->write(msg);
            }
        }
        
        void Session_Core::write(const Char* msg, uint16_t length)
        {
            ChatMessage cm(msg, length);
            do_write(cm);
        }
        
        void Session_Core::write(const String& msg)
        {
            ChatMessage cm(msg);
            do_write(cm);
        }
        
        void Session_Core::write(const ChatMessage& msg)
        {
            ChatMessage cm(msg);
            do_write(cm);
        }
        
        Session_Core& Session_Core::operator<<(const String& msg)
        {
            write(msg);
            return *this;
        }
        
        Session_Core& Session_Core::operator<<(const ChatMessage& msg)
        {
            write(msg);
            return *this;
        }
        
        void Session_Core::do_write(ChatMessage& msg)
        {
            bool writeInProgress = !messageQueue.empty();
            messageQueue.push_back(msg);
            
            if (!writeInProgress)
            {
                StringStream ss;
                ss << ">> " << msg.body();
                logger.log<LOGGINGTYPE::DEBUG>(ss.str() );
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(msg.data(),
                                                             msg.length()),
                                         boost::bind(&Session_Core::handleWrite,
                                                     this,
                                                     boost::asio::placeholders::error));
            }
        }
        
        void Session_Core::handleWrite(const boost::system::error_code& error)
        {
            if (!error)
            {
                messageQueue.pop_front();
                if (!messageQueue.empty())
                {
                    ChatMessage& msg = messageQueue.front();
                    boost::asio::async_write(socket_,
                                             boost::asio::buffer(msg.data(),
                                                                 msg.length()),
                                             boost::bind(&Session_Core::handleWrite,
                                                         this,
                                                         boost::asio::placeholders::error));
                }
            }
            else
            {
                disconnect();
            }
        }
        
        void Session_Core::close()
        {
            io_service_.post(boost::bind(&Session_Core::do_close, this));
        }
        
        void Session_Core::do_close()
        {
            socket_.close();
        }
        
        void Session_Core::enterCommandLoop()
        {
            if (!isInCommandLoop)
            {
                isInCommandLoop = true;
                asyncRead<Session_Core>(&Session_Core::commandLoop);
            }
        }
        
        void Session_Core::commandLoop(Char* buffer,
                                       const boost::system::error_code& error,
                                       size_t /*bytes_transferred*/)
        {
            isInCommandLoop = false;
            if (!error)
            {
                // loop aufrecht erhalten, und das so früh wie möglich
                enterCommandLoop();
                // hier fangen wir commands ab
                ChatMessage rm(buffer);
                requestCommand(rm);
            }
            else
            {
                disconnect();
            }
        }
        
        void Session_Core::disconnect()
        {
            unmakePublic();
            atDisconnect();
            
            delete this;
        }
        
        String& Session_Core::operator[](String& key)
        {
            return _values[key];
        }
    }
}
