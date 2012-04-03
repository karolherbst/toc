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

#ifndef LIB_TOCLOGGER_MULTITHREADEDPROCESSOR
#define LIB_TOCLOGGER_MULTITHREADEDPROCESSOR 1

#include <boost/thread/thread.hpp>
#include <queue>

namespace TOC
{
    #define TEMPLATE_CLASS_DEF template <class Task>
    #define TEMPLATE_CLASS_ARG <Task>

    TEMPLATE_CLASS_DEF
    class MultiThreadedProcessor
    {
    public:
        template <class StringType>
        void
        add(StringType str);

        MultiThreadedProcessor();
        ~MultiThreadedProcessor();

    private:
        boost::thread log_thread;
        mutable boost::mutex log_mutex;
        boost::condition_variable log_cond;
        std::queue<std::string> msgs;

        void thread_execute();
    };

    TEMPLATE_CLASS_DEF
    MultiThreadedProcessor TEMPLATE_CLASS_ARG::
    MultiThreadedProcessor()
    :   log_thread( boost::bind( &MultiThreadedProcessor::thread_execute, this) )
    {}

    TEMPLATE_CLASS_DEF
    MultiThreadedProcessor TEMPLATE_CLASS_ARG::
    ~MultiThreadedProcessor()
    {
        log_thread.interrupt();
        log_thread.join();
    }

    TEMPLATE_CLASS_DEF
    template <class StringType>
    void
    MultiThreadedProcessor TEMPLATE_CLASS_ARG::
    add(StringType str)
    {
        if(!msgs.empty())
            msgs.push(str);
        else
        {
            boost::mutex::scoped_lock lock(log_mutex);
            msgs.push(str);
            lock.unlock();
            log_cond.notify_one();
        }
    }

    TEMPLATE_CLASS_DEF
    void
    MultiThreadedProcessor TEMPLATE_CLASS_ARG::
    thread_execute()
    {
        while(true)
        {
            boost::mutex::scoped_lock lock(log_mutex);
            while(msgs.empty())
            {
                log_cond.wait(lock);
            }

            std::string value = msgs.front();
            msgs.pop();
            lock.unlock();
            Task::run(value);

            if(msgs.empty())
                boost::this_thread::interruption_point();
        }
    }


    #undef TEMPLATE_CLASS_DEF
    #undef TEMPLATE_CLASS_ARG
}


#endif //LIB_TOCLOGGER_THREADEDPROCESSOR
