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

#ifndef LIB_TOCDB_ABSTRACTQUERYBUILDER
#define LIB_TOCDB_ABSTRACTQUERYBUILDER 1

#include <map>
#include <queue>

#include <toc/tocdb/DBTypes.h>
#include <toc/tocexception/CoreException.h>
#include <toc/tocstring/TocString.h>

#include <boost/extension/impl/decl.hpp>
#ifndef DLL_TOC_DB
#ifdef MAKE_TOC_DB
#define DLL_TOC_DB BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_DB BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace TOC
{
    namespace DB
    {
        COREEXCEPTION_SUBCLASS(QueryIsBrokenException,
                               "the current query is broken!");
        
        /**
		 * @class AbstractQueryBuilder
		 *
		 * An interface for querybuilder
         *
         * DO NOT use instances of this class in your application directly.
         * this class should be use for implementing a querybuild only. This
         * is necassary when you implement a own TocDBDriver. The TocDB library
         * will manage all access to the underlining database itself through
         * TocDBDriver
         *
         * If you dont understand this please read the article about programming
         * with TocDB an all conceptuals parts of the documentation.
         *
         * @see DB for more informations
		 *
		 * @author	Karol Herbst
		 * @since	0.1
		 */
        class DLL_TOC_DB AbstractQueryBuilder
        {
        public:
			/**
			 * destructor
			 *
			 * @author	Karol Herbst
			 * @since	0.1
			 */
		    virtual	~AbstractQueryBuilder();
            
			/**
			 * add key value pair for adding conditions
			 * will be depracted in a future version
			 *
			 * @param	key		the key
			 * @param	value	the value
			 *
			 * @author	Karol Herbst
			 * @since	0.1
			 */
            void addWherePair(const String& key,
                              const String& value);
			
			/**
             * add key value pair for ordering result set
             * will be depracted in a future version
             *
			 * @param	key		the key
			 * @param	order	the order
			 *
             * @author  Karol Herbst
             * @since   0.1
             */
            void addOrderPair(const String& key,
                              TOC::ORDER order = TOC::ORDER::ASC);
			
			/**
			 * @return	the name of the current entityclass
			 *
			 * @author	Karol Herbst
			 * @since	0.1
			 */
			virtual const String entityclass() const = 0;
			
            /**
             * @param   entityclass     the new entityclass
             *
             * @author  Karol Herbst
             * @since   0.1
             */
			virtual void entityclass(const String & entityclass) = 0;

            /**
             * @return   the actual attribute
             *
             * @author  Karol Herbst
             * @since   0.1
             */
			virtual const String attribute() const = 0;
            
            /**
             * @param   attribute   the new attribute
             *
             * @author  Karol Herbst
             * @since   0.1
             */
			virtual void attribute(const String & attribute) = 0;
            
            /**
             * @return  the actual id
             *
             * @author  Karol Herbst
             * @since   0.1
             */
			virtual const uint64_t id() const = 0;
            
            /**
             * @param   id  the new id
             *
             * @author  Karol Herbst
             * @since   0.1
             */
			virtual void id(const uint64_t & id) = 0;
			
            
            /**
             * creates a transaction in the DB driver
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual String startTransaction() = 0;
            
            /**
             * commit the current transaction
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual String commitTransaction() = 0;
            
            /**
             * rollback current changes
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual String rollbackTransaction() = 0;
            
            /**
             * creates a query to create a simple entityclass
             *
             * @pre     a entityclass name is set
             * @return  a query, which creates an empty table with a ID
             *          key-coloum with type DBInt
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual String buildCreateEntityClassQuery() = 0;
            
            /**
             * creates a query to create a relation entityclass between to others
             *
             * between the entityclass there must be a linear relationship
             *
             * @param   t1  the "parent" entityclass
             * @param   t2  the "child" entityclass
             * @pre     a relation-entityclass name is set
             *
             * @return  q query to build a new entityclass, which will automatically
             *          delete all childs when the parent entity is deleted
             *
             * @author  Karol Herbst
             * @since   0.1
             *
             * @todo    what should we do with non-linear relationships?
             */
            virtual String buildRelationEntityClassQuery(const String& t1,
                                                         const String& t2) = 0;
            
            /**
             * create a query to add a coloum to a given entityclass
             *
             * @param   defaultValue    the defaultValue for each entity
             * @param   type            the abstract db type (DBType)
             * @param   size            the size of the data (number of chars, Dezimalstellen)
             * @pre     a entityclass and a attribute is set
             *
             * @author  Karol Herbst
             * @since   0.1
             *
             * @todo    link to DBTypes
             */
            virtual String buildAddAttributeQuery(const String& defaultValue,
                                                  const String& type,
                                                  const int16_t size) = 0;
            
            /**
             * creates a query, which selects a whole entity
             *
             * @pre     a entityclass and a id is set
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual String buildIDSelectQuery() = 0;
            
            /**
             * use this method if you wanna fetch a value from one entity only
             *
             * @pre     entityclass, id and attribute is set
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual String buildSingleValueSelectQuery() = 0;
            
            /**
             * use this method if you wanna fetch a whole attribute set from an
             * entityclass
             *
             * @pre     entityclass and attribute is set
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual String buildSingleAttributeSelectQuery() = 0;
            
            /**
             * use this method to inset a specific value into an entity
             *
             * @pre     entityclass, id and attribute is set
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            virtual String buildSingleValueInsertQuery(const String& attribute) = 0;
            virtual String buildIdInsertQuery(std::map<String, String>&) = 0;
        protected:
            typedef std::pair<String, TOC::ORDER> OrderPair;
            
            std::queue<String> keys;
            std::queue<String> values;
            std::queue<OrderPair> orders;
        };
    }
}

#endif //LIB_TOCDB_ABSTRACTQUERYBUILDER

