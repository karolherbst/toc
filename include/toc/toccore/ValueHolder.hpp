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

#ifndef LIB_TOCCORE_VALUEHOLDER
#define LIB_TOCCORE_VALUEHOLDER 1

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>

namespace TOC
{
    namespace core
    {
        template <class T, class O>
        class ValueObserver : boost::operators<T>
        {
        public:
            ValueObserver(T&, O*, void (O::*)(const T&, uint16_t), uint16_t);
            
            ValueObserver<T, O>& operator=(const T &);
            T* operator->();
            operator const T&();
            bool operator==(const T&);
            
            friend std::ostream&
            operator<<(std::ostream& ostr,
                       const ValueObserver<T, O>& m)
            {
                return ostr << m.v;
            }
            
        private:
            T& v;
            uint16_t i;
            O* o;
            void (O::*notifyChangeFunc)(const T&, uint16_t);
        };
        
        template <class T, class O>
        ValueObserver<T, O>::
        ValueObserver(T &t, O *_o, void (O:: *_func)(const T&, uint16_t), uint16_t _i)
        :   v(t),
        i(_i),
        o(_o),
        notifyChangeFunc(_func)
        {
            
        }
        
        template <class T, class O>
        ValueObserver<T, O>&
        ValueObserver<T, O>::
        operator=(const T &t)
        {
            boost::bind(notifyChangeFunc,
                        o,
                        t,
                        i)();
            return *this;
        }
        
        template <class T, class O>
        bool
        ValueObserver<T, O>::
        operator==(const T& t)
        {
            return v == t;
        }
        
        template <class T, class O>
        ValueObserver<T, O>::
        operator const T&()
        {
            return v;
        }
    }
}

#endif //LIB_TOCCORE_VALUEHOLDER
