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

#ifndef LIB_TOCDB_LISTATTRIBUTE
#define LIB_TOCDB_LISTATTRIBUTE 1

#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr/shared_array.hpp>
#include <toc/toccore/ValueHolder.hpp>
#include <toc/tocdb/CoreAttribute.h>
#include <toc/tocdb/DBRow.h>
#include <vector>

namespace TOC
{
    namespace DB
    {
#define TEMPLATE_PARAS template <class A, class M, class I, uint16_t s, bool c>
        
        TEMPLATE_PARAS
        class ListAttribute : public CoreAttribute< A* , M, I, c, boost::shared_array>
        {
        public:
            typedef core::ValueObserver<A, ListAttribute<A, M, I, s, c> > Type;
            
            ListAttribute(M* m);
            virtual ~ListAttribute();
            
            Type operator[](uint16_t);
        private:
            boost::shared_array<A*>& ptr();
            
            void observer(const A&, uint16_t);
        };
        
        TEMPLATE_PARAS
        ListAttribute<A, M, I, s, c>::
        ListAttribute(M* m)
        :   CoreAttribute<A*, M, I, c, boost::shared_array>(m)
        {
            if ( this->parent->id() == 0 )
            {
                DBTable t = DB::Instance()[M::table];
                for (uint16_t i; i < s; i++)
                {
                    t[I::name + lexical_cast<String>(i)]
                        .create(I::defaultValue,
                                I::type,
                                I::size);
                }
            }
        }
        
        TEMPLATE_PARAS
        ListAttribute<A, M, I, s, c>::
        ~ListAttribute()
        {
            //if (this->_ptr.get() != NULL)
            //    for (uint16_t i = 0; i < I::size; i++)
            //        delete ptr().get()[i];
        }
        
        TEMPLATE_PARAS
        core::ValueObserver<A, ListAttribute<A, M, I, s, c> >
        ListAttribute<A, M, I, s, c>::
        operator[](uint16_t i)
        {
            return Type( *ptr()[i],
                        this,
                        &ListAttribute<A, M, I, s, c>::observer,
                        i);
        }
        
        TEMPLATE_PARAS
        boost::shared_array<A*>&
        ListAttribute<A, M, I, s, c>::
        ptr()
        {
            if (this->_ptr.get() == NULL)
            {
                A** list = new A*[I::size];
                this->_ptr.reset(list);
                try
                {
                    DBTable t = DB::Instance()[M::table];
                    DBRow r = t[this->parent->id()];
                    for (uint16_t i = 0; i < I::size; i++)
                    {
                        String col = I::name + lexical_cast<String>(i);
                        list[i] = new A( boost::lexical_cast<A>(r[col]) );
                    }
                }
                // the only exception, we can catch here ist an empty result
                catch(core::CoreException&)
                {
                    // fill with default values;
                    for (uint16_t i = 0; i < I::size; i++)
                        list[i] = new A( lexical_cast<A>(I::defaultValue) );
                }
            }
            return this->_ptr;
        }
        
        TEMPLATE_PARAS
        void
        ListAttribute<A, M, I, s, c>::
        observer(const A &a, uint16_t i)
        {
            if (!CoreTransaction::isThereAContext())
                throw NoTransactionException();
            CoreTransaction::addDataPatch(new SingleValuePatch(M::table,
                                                               this->parent->id(),
                                                               I::name + lexical_cast<String>(i),
                                                               a));
        }
        
#undef TEMPLATE_PARAS
    }
}

#endif //LIB_TOCDB_LISTATTRIBUTE
