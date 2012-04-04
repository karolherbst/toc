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

#ifndef LIB_TOCCORE_RELATIONATTRIBUTE
#define LIB_TOCCORE_RELATIONATTRIBUTE 1

#include <toc/tocdb/CoreAttribute.h>
#include <toc/tocdb/DB.h>
#include <toc/tocdb/DBTypes.h>

#define db TOC::DB::DB::Instance()

namespace TOC
{
    namespace DB
    {
        template <class A,
        class M,
        bool c = true>
        class RelationAttribute : public CoreAttribute<std::vector<boost::shared_ptr<A> >,
        M,
        ListAtt<M, A>,
        c>
        {
        public:
            RelationAttribute(M*);
            typedef shared_ptr<std::vector<boost::shared_ptr<A> > > Ptr;
            typedef CoreAttribute<std::vector<boost::shared_ptr<A> >, M, ListAtt<M, A>, c> super;
            
            RelationAttribute<A, M, c>& insert(uint16_t, const A&);
            
            operator std::vector<A*>();
            
        protected:
            virtual shared_ptr<std::vector<boost::shared_ptr<A> > >& ptr();
        };
        
        template <class A, class M, bool c>
        RelationAttribute<A, M, c>::
        RelationAttribute(M* m)
        :   CoreAttribute<std::vector< boost::shared_ptr<A> >,
        M,
        ListAtt<M, A>,
        c>(m)
        {
            if ( this->parent->id() == 0 )
            {
                db[M::table].connectWith(A::table)
                    [ListAtt<M, A>::name].create(ListAtt<M, A>::defaultValue,
                                                 ListAtt<M, A>::type,
                                                 ListAtt<M, A>::size);
            }
        }
        
        template <class A, class M, bool c>
        shared_ptr<std::vector<boost::shared_ptr<A> > >&
        RelationAttribute<A, M, c>::
        ptr()
        {
            if (this->_ptr.get() == NULL)
            {
                std::vector<boost::shared_ptr<A> >* list = new std::vector< boost::shared_ptr<A> >();
                try
                {
                    // we get the ids first
                    std::vector<String> vec;// = *this->_ptr;
                    (db[M::table + '_' + A::table][A::table].where(M::table, lexical_cast<String>(this->parent->id()) ).order(ListAtt<M, A>::name, ASC) ) >> vec;
                    foreach(const String& id, vec)
                        list->push_back( boost::shared_ptr<A>(new A(lexical_cast<uint64_t>(id)) ) );
                    this->_ptr.reset(list);
                }
                // the only exception, we can catch here ist an empty result
                catch(core::CoreException&)
                {
                    this->_ptr.reset(list);
                    //super::operator=(list);
                }
            }
            return this->_ptr;
        }
        
        template <class A, class M, bool c>
        RelationAttribute<A, M, c>&
        RelationAttribute<A, M, c>::
        insert(uint16_t pos, const A& a)
        {
            if (!CoreTransaction::isThereAContext())
                throw NoTransactionException();
            std::map<String, String> values;
            values[M::table] = lexical_cast<String>(this->parent->id());
            values[A::table] = lexical_cast<String>(a.id());
            values[ListAtt<M, A>::name] = lexical_cast<String>(pos);
            
            // update ptr
            CoreTransaction::addDataPatch(new SingleRowPatch(M::table + '_' + A::table,
                                                             values));
            return *this;
        }
        
        template <class A, class M, bool c>
        RelationAttribute<A, M, c>::
        operator std::vector<A*>()
        {
            std::vector<A*> result;
            std::vector<boost::shared_ptr<A> >& list = *ptr();
            
            for (size_t i = 0; i < list.size(); i ++)
                result.push_back(list[i].get());
            
            return result;
        }
    }
}

#undef db

#endif //LIB_TOCCORE_RELATIONATTRIBUTE
