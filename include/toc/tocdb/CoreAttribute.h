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
 
 I stores all necessary Information about the attribute like Type, Length, etc...
 
 wie soll diese Klasse funktionieren:
 
 changeable = true
 ? originale Daten werden in einem statischen Array via shared_ptr gespeichert
 es sollen jederzeit Referenzen über weak_ptr aufgebaut werden können.
 Daten werden nur lokal überschrieben und erst in einer Transaktion zusammen in einer DB gespeichert.
 
 */

#ifndef LIB_TOCCORE_COREATTRIBUTE
#define LIB_TOCCORE_COREATTRIBUTE 1

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <toc/tocdb/CoreTransaction.h>
#include <toc/tocdb/DataPatch.h>
#include <toc/tocdb/Information.h>
#include <toc/tocdb/StandardTypes.h>
#include <toc/tocexception/CoreException.h>

namespace TOC
{
    namespace DB
    {
        using boost::shared_ptr;
        
        COREEXCEPTION_SUBCLASS(AttributeException,
                               "critical failure occured within accessing an Attribute");
        SUBCLASS_OF_COREXCEPTION_SUBCLASS(AttributeException,
                                          AttributeChangedWhileAccessingException,
                                          "the value of the attribute has changed!");
        
        template <class A,
        class M,
        class I,
        // changeable:
        bool c = true,
        template <class> class H = shared_ptr >
        class CoreAttribute
        {
        public:
            typedef A AttributeType;
            typedef M Model;
            typedef I Information;
            typedef H<A> Holder;
            
            CoreAttribute(M*);
            virtual ~CoreAttribute(){};
            void operator=(const A& value);
            
            operator const A ();
            const A* operator->();
            
            template <class _A, class _M, class _I, bool _c, template <class> class _H>
            friend std::ostream&
            operator<<(std::ostream &ostr,
                       CoreAttribute<_A, _M, _I, _c, _H> &m);
        protected:
            // only access via ptr()
            Holder _ptr;
            // => impl in special classes
            virtual Holder& ptr() = 0;
            M* parent;
            // only changeable
        private:
            CoreAttribute();
        };
        
        template <class A, class M, class I, bool c, template <class> class H>
        CoreAttribute<A, M, I, c, H>::
        CoreAttribute(M* m)
        :   parent(m)
        {
            
        }
        
        template <class A, class M, class I, bool c, template <class> class H>
        void
        CoreAttribute<A, M, I, c, H>::
        operator=(const A& value)
        {
            if (!CoreTransaction::isThereAContext())
                throw NoTransactionException();
            _ptr.reset(new A(value));
            CoreTransaction::addDataPatch(new SingleValuePatch(M::table,
                                                               this->parent->id(),
                                                               I::name,
                                                               lexical_cast<String>(value)));
            }
        
        template <class A, class M, class I, bool c, template <class> class H>
        CoreAttribute<A, M, I, c, H>::
        operator const A ()
        {
            return *ptr();
        }
        
        template <class A, class M, class I, bool c, template <class> class H>
        const A*
        CoreAttribute<A, M, I, c, H>::
        operator->()
        {
            return ptr().get();
        }
        
        /// free functions
        template <class A, class M, class I, bool c, template <class> class H>
        std::ostream &operator<<(std::ostream &ostr, CoreAttribute<A, M, I, c, H> &m) 
        {
            return ostr << *m.ptr();
        }
    }
}

#endif //LIB_TOCCORE_COREATTRIBUTE
