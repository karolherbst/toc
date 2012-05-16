#include <boost/noncopyable.hpp>
#include <toc/boost/extension/extension.hpp>
#include <toc/tocdb/AbstractQueryBuilder.h>
#include <toc/tocdb/StandardTypes.h>

namespace TOC
{
    namespace DB
    {
        class BOOST_EXTENSION_EXPORT_DECL MySQLQueryBuilder : public AbstractQueryBuilder, boost::noncopyable
        {
        public:
            //transactions, locks, etc...
            static String StartTransaction();
            static String CommitTransaction();
            static String RollbackTransaction();
            String startTransaction();
            String commitTransaction();
            String rollbackTransaction();
            
            String buildIdInsertQuery(std::map<String, String>&);
            String buildRelationEntityClassQuery(const String&,
                                                 const String&);
            String buildCreateEntityClassQuery();
            String buildAddAttributeQuery(const String& defaultValue,
                                          const String& _type,
                                          const int16_t size);
            String buildSingleAttributeSelectQuery();
            
            // selects
            String buildIDSelectQuery();
            String buildSingleValueSelectQuery();
            
            // inserts
            String buildSingleValueInsertQuery(const String&);

			const uint64_t id() const;
			void id(const uint64_t&);

			const String attribute() const;
			void attribute(const String&);

			const String entityclass() const;
			void entityclass(const String&);

			static AbstractQueryBuilder* newQueryBuilder();
        private:
            template<class T>
            void buildOrderPart(T& ss);
            template<class T>
            void buildWherePart(T& ss);

			uint64_t _id;
			String  _attribute;
			String  _entityclass;
        };
    }
}
