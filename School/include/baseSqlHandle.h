#ifndef BASE_SQL_HANDLE_H
#define BASE_SQL_HANDLE_H
#include <mysql.h>

#include "baseEntry.h"
#include "baseSqlUrl.h"
#include "baseSqlRecord.h"
#include "baseSqlTable.h"
#include "baseLock.h"
#include "baseTime.h"

class MysqlPool;

enum HandleState
{
	HandleState_Invalid = 1,  //无效
	HandleState_Valid   = 2,  //有效
	HandleState_Used    = 3   //使用
};
class MysqlHandle : public Entry
{
	public:
		const char* getClassName() const
		{
			return "MysqlHandle";
		}
	private:
		DWORD _hashcode;
		const MysqlUrl *_url;
		DWORD _count;
		Time lifeTime;
		MYSQL *_mysql;
		bool initMysql();
		Time _use_time;
 		DWORD _timeout_time;
		Time _update_time;
		Time _insert_time;
		Time _delete_time;
		Time _select_time;
	public:
		MysqlPool *pool;
		HandleState state;
		Time useTime;
		std::string lastsql;
		MysqlHandle(const MysqlUrl *url,MysqlPool *_pool,DWORD hashcode);
		~MysqlHandle();
		MYSQL* getMysql() const
		{
			return _mysql;
		}
		bool initHandle();
		void finalHandle();
		bool setHandle();
		void freeHandle();
		void checkUseTime();
		SDWORD execSql(const char *sql,DWORD sqllen,bool need_errlog = true);
		RecordSet* exeSelect(const char *sql,DWORD sqllen);
		RecordSet* exeSelect(const char *tableName,Record *column,Record *where,Record *having,DWORD limit_offset = 0,DWORD limit_rows = 0,Record *groupby=NULL,Record *order= NULL);
		DWORD exeInsert(const char *tableName,Record *data,bool need_errlog = true);
		DWORD exeUpdate(const char *tableName,Record *data,Record *where);
		DWORD exeDelete(const char *tableName,Record *where);
		char* escapeString(const char *src,char *dest,DWORD size);
		std::string& escapeString(const std::string &src,std::string &dest);
		bool escapeString(const char *src);
		bool escapeString(const std::string &src);
	private:
		inline std::ostringstream& getWhere(Table *table,std::ostringstream &query_string,Record *where);
		inline std::ostringstream& getGroupBy(Table *table,std::ostringstream &query_string,Record *groupby);
		inline std::ostringstream& getHaving(Table *table,std::ostringstream &query_string,Record *having);
		inline std::ostringstream& getOrder(Table *table,std::ostringstream &query_string,Record *order);
		inline std::ostringstream& storeValue(Table *table,std::ostringstream &query_string,const SDWORD type,const ValType &value);
};

class MysqlHandleManager : public EntryManager<EntryID,EntryNone<2>,EntryNone<3>,true>/*,public Singletonbase<MysqlHandleManager>*/
{
	public:
		MysqlHandleManager()
		{
		}
		~MysqlHandleManager()
		{
			deleteAll();
		}
		bool addMysqlHandle(MysqlHandle *entry)
		{
			bool ret = false;
			rwlock.wrlock();
			ret = addEntry(entry);
			rwlock.unlock();
			return ret;
		}
		void removeMysqlHandle(MysqlHandle *entry)
		{
			rwlock.wrlock();
			removeEntry(entry);
			rwlock.unlock();
		}
		MysqlHandle* getMysqlHandleByID(DWORD handleid)
		{
			MysqlHandle *ret = NULL;
			rwlock.rdlock();
			ret = (MysqlHandle*)getEntryByID(handleid);
			return ret;
		}
		size_t getSize()
		{
			return EntryManager<EntryID,EntryNone<2>,EntryNone<3>,true>::size();
		}
		template <class YourEntry>
		bool execEveryMysqlHandle(EntryCallBack<YourEntry> &exec)
		{
			rwlock.rdlock();
			bool ret = execEveryEntry<>(exec);
			rwlock.unlock();
			return ret;
		}
	private:
		RWLock rwlock;
};



#endif
