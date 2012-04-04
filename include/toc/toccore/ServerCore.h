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

#ifndef LIB_TOCCORE_SERVERCORE
#define LIB_TOCCORE_SERVERCORE 1

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace TOC
{
    namespace core
    {
        class Session_Core;
        
        template <class Session = bool>
        class ServerCore
        {
        private:
            boost::asio::io_service& io_service_;
            boost::asio::ip::tcp::acceptor acceptor_;
            
            void handle_accept(Session_Core* newSession,
                               const boost::system::error_code& error);
            
            Session* makeNewSession();
            
        public:
            ServerCore(boost::asio::io_service& io_service,
                       uint16_t port);
            ~ServerCore();
            
            void run();
            void stop();
        };
        
#include <boost/bind.hpp>
#include <toc/toccore/SessionCore.h>
        
        using boost::asio::ip::tcp;
        
        template <class Session>
        ServerCore<Session>::
        ServerCore(boost::asio::io_service& io_service,
                   uint16_t port)
        :   io_service_(io_service),
        acceptor_(io_service_,
                  tcp::endpoint(tcp::v4(),
                                port))
        {
            
        }
        
        template <class Session>
        ServerCore<Session>::
        ~ServerCore()
        {
            
        }
        
        template <class Session>
        void
        ServerCore<Session>::
        handle_accept(Session_Core* newSession,
                      const boost::system::error_code& error)
        {
            if (!error)
            {
                newSession->start();
                newSession = makeNewSession();
                acceptor_.async_accept(newSession->socket(),
                                       boost::bind(&ServerCore::handle_accept,
                                                   this,
                                                   newSession,
                                                   boost::asio::placeholders::error));
            }
            else
            {
                delete newSession;
            }
        }
        
        template <class Session>
        void
        ServerCore<Session>::
        run()
        {
            try
            {
                Session* newSession = makeNewSession();
                acceptor_.async_accept(newSession->socket(),
                                       boost::bind(&ServerCore::handle_accept,
                                                   this,
                                                   newSession,
                                                   boost::asio::placeholders::error));
                io_service_.run();
                //boost::this_thread::interruption_point();
            }
            catch (boost::thread_interrupted& e)
            {
                
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        
        template <class Session>
        void
        ServerCore<Session>::
        stop()
        {
            //#warning close all sessions here
        }
        
        template <class Session>
        Session*
        ServerCore<Session>::
        makeNewSession()
        {
            return new Session(io_service_);
        }
    }
}

#endif //LIB_TOCCORE_SERVERCORE
