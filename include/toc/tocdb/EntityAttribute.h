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

#ifndef LIB_TOCCORE_ENTITYATTRIBUTE
#define LIB_TOCCORE_ENTITYATTRIBUTE 1

#include <toc/tocdb/CoreAttribute.h>
#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBCol.h>
#include <toc/tocdb/DBTable.h>
#include <toc/tocdb/DBValue.h>

#define db TOC::DB::DB::Instance()

namespace TOC
{
    namespace DB
    {
        template <class A, class M, class I, bool c = true>
        class EntityAttribute
        :   public CoreAttribute<A, M, I, c>
        {
        public:
            EntityAttribute(M*);
            virtual ~EntityAttribute(){};
            
            typedef CoreAttribute<A, M, I, c> super;
            
            void operator=(const A value);
            
        protected:
            virtual shared_ptr<A>& ptr();
        };
        
        template <class A, class M, class I, bool c>
        EntityAttribute<A, M, I, c>::
        EntityAttribute(M* m)
        :   CoreAttribute<A,
        M,
        I,
        c>(m)
        {
            if ( this->parent->id() == 0 )
            {
                db[M::table][I::name].create(I::defaultValue,
                                             I::type,
                                             I::size);
            }
        }
        
        template <class A, class M, class I, bool c>
        void
        EntityAttribute<A, M, I, c>::
        operator=(const A value)
        {
            super::operator=(value);
        }
        
        template <class A, class M, class I, bool c>
        shared_ptr<A>&
        EntityAttribute<A, M, I, c>::
        ptr()
        {
            if (this->_ptr.get() == NULL)
                try
            {
                this->_ptr.reset( new A( lexical_cast<A>(db[M::table][I::name][this->parent->id()])));
            }
            // the only exception, we can catch here ist an empty result
            catch(core::CoreException&)
            {
                this->_ptr.reset(new A(lexical_cast<A>(I::defaultValue)));
                super::operator=(lexical_cast<A>(I::defaultValue));
            }
            return this->_ptr;
        }
    }
}

#undef db

#endif //LIB_TOCCORE_ENTITYATTRIBUTE
