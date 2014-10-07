#include "baseSqlHandle.h"
#include "baseSqlPool.h"

MysqlHandle::MysqlHandle(const MysqlUrl *url,MysqlPool *pool,DWORD hashcode)
{
	static DWORD _tempid = 0;
	_tempid++;
	id = _tempid;
	_url = url;
	state = HandleState_Invalid;
	_mysql = NULL;
	_timeout_time = 10000L;
	this->pool = pool;
	this->_hashcode = hashcode;
}
MysqlHandle::~MysqlHandle()
{
	finalHandle();
}

bool MysqlHandle::initMysql()
{
	if(_mysql)
	{
		mysql_close(_mysql);
		_mysql = NULL;
	}
	_mysql = mysql_init(NULL);
	if(!_mysql)
	{
		Test::logger->error("MysqlHandle::initMysql error _mysql is NULL ");
		return false;
	}
	if(!mysql_real_connect(_mysql,_url->host,_url->user,_url->passwd,NULL,_url->port,NULL,CLIENT_COMPRESS|CLIENT_INTERACTIVE))
	{
		Test::logger->error("MysqlHandle::initMysql error connect faild host:%s,port:%d,passwd:%s",_url->host,_url->port,_url->passwd);
		return false;
	}
	state = HandleState_Valid;
	lifeTime.now();
	_count = 0;
	return true;
}
bool MysqlHandle::initHandle()
{
	finalHandle();
	if(!initMysql())
	{
		finalHandle();
		return false;
	}
	return true;
}
void MysqlHandle::finalHandle()
{
	if(_mysql)
	{
		mysql_close(_mysql);
		_mysql = NULL;
	}
	state = HandleState_Invalid;
	_count = 0;
	lastsql = "";
}
bool MysqlHandle::setHandle()
{
	if(state == HandleState_Used)
	{
		return false;
	}
	_use_time.now();
	if(_count > 10000 || mysql_ping(_mysql))
	{
		if(!initHandle())
		{
			return false;
		}
	}
	state = HandleState_Used;
	++_count;
	return true;
}
void MysqlHandle::freeHandle()
{
	state = HandleState_Valid;
}
void MysqlHandle::checkUseTime()
{
	if(_use_time.elapse(Time()) > _timeout_time)
	{
		_timeout_time += 10000L;
	}
	
}
int MysqlHandle::execSql(const char *sql,unsigned int sqllen,bool need_errlog)
{
	if(!sql || !sqllen || !_mysql)
	{
		Test::logger->debug("MysqlHandle::execSql arg is error");
		return -1;
	}
	lastsql = sql;
	int ret = mysql_real_query(_mysql,sql,sqllen);
	if(ret && need_errlog)
	{
		Test::logger->debug("MysqlHandle::execSql error %s",mysql_error(_mysql));
	}
	return ret;
}
RecordSet* MysqlHandle::exeSelect(const char *sql,unsigned int sqllen)
{
	if(!_mysql)
	{
		return NULL;
	}
	_select_time.now();
	if(execSql(sql,sqllen))
	{
		Test::logger->error("MysqlHandle::exeSelect error %s",mysql_error(_mysql));
		return NULL;
	}
	MYSQL_RES *result = NULL;
	result = mysql_store_result(_mysql);
	if(!result)
	{
		return NULL;
	}
	DWORD retCount = mysql_num_rows(result);
	if(!retCount)
	{
		mysql_free_result(result);
		return NULL;
	}
	MYSQL_ROW row;
	DWORD num_filed = mysql_num_fields(result);
	MYSQL_FIELD *mysql_fileds = mysql_fetch_fields(result);
	RecordSet *ret_set = NULL;
	if(mysql_num_rows(result))
	{
		ret_set = new RecordSet(retCount);
		if(!ret_set)
		{
			return NULL;
		}
		DWORD index = 0;
		while(row = mysql_fetch_row(result))
		{
			QWORD *lengths = mysql_fetch_lengths(result);
			Record *rec = ret_set->get(index++);
			if(!rec)
			{
				return NULL;
			}
			for(DWORD filedCnt = 0;filedCnt < num_filed;++filedCnt)
			{
				if(row[filedCnt])
				{
					rec->put(mysql_fileds[filedCnt].name,row[filedCnt],lengths[filedCnt]);
				}
			}
		}
	}
	mysql_free_result(result);
	if(ret_set && !ret_set->size())
	{
		DELETE(ret_set);
	}
	if(_select_time.elapse(Time()) >= 3 * 1000L)
	{
		Test::logger->debug("MysqlHandle::exeSelect sql:%s 超时:%lu毫秒",sql,_select_time.elapse(Time()));
	}
	return ret_set;
}
DWORD MysqlHandle::exeInsert(const char *tableName,Record *data,bool need_log)
{
	Table *table = pool->tm[_hashcode]->getTableByName(tableName);
	if(!table || !data || !_mysql)
	{
		Test::logger->debug("MysqlHandle::exeInsert error argument is error tableName:%s",tableName);
		return (DWORD)-1;
	}
	_insert_time.now();
	std::ostringstream query_string;
	std::ostringstream value_string;
	query_string << "INSERT INTO ";
	query_string << "'" << table->name << "'";
	query_string << " ( ";
	value_string << " VALUES( ";
	struct InsertExec : public EntryCallBack<Filed>
	{
		bool _frist;
		Table *_table;
		std::ostringstream &query_string;
		std::ostringstream &value_string;
		MysqlHandle *_handle;
		InsertExec(Table *table,std::ostringstream &query_string,std::ostringstream &value_string):_frist(true),_table(table),query_string(query_string),value_string(value_string)
		{
		}
		bool exec(Filed *entry)
		{
			Filed *basefiled = _table->fs.get(entry->name);
			if(!basefiled)
			{
				return true;
			}
			if(!_frist)
			{
				_frist = false;
			}
			else
			{
				query_string << " , ";
				value_string << " , ";
				query_string << "'" << entry->name << "'";
				_handle->storeValue(_table,value_string,basefiled->type,entry->data);
				return true;
			}
		}
	}dcb(table,query_string,value_string);
	data->execEveryFiled(dcb);
	query_string << ")" << value_string.str() << ")";	 DWORD ret = (DWORD)-1;
	if(!execSql(query_string.str().c_str(),query_string.str().size(),need_log))
	{
		ret = (DWORD)mysql_insert_id(_mysql);
	}
	if(_insert_time.elapse(Time()) >= 3 * 1000L)
	{
		Test::logger->debug("MysqlHandle::exeInsert sql :%s 超时: %lu",query_string.str().c_str(),_select_time.elapse(Time()));
	}
	return ret;
}
unsigned int MysqlHandle::exeUpdate(const char *tableName,Record *data,Record *where)
{
	Table *table = this->pool->tm[this->_hashcode]->getTableByName(tableName);
	if(!table || !data || !_mysql)
	{
		return (DWORD)-1;
	}
	_update_time.now();
	std::ostringstream query_string;
	query_string << "UPDATE ";
	query_string << "'" << table->name <<"'";
	query_string << " SET ";
	struct UpdateExec : public EntryCallBack<Filed>
	{
		bool _frist;
		Table *_table;
		std::ostringstream &query_string;
		MysqlHandle *_handle;
		UpdateExec(Table *table,std::ostringstream &_query_string,MysqlHandle *handle):_frist(true),_table(table),query_string(_query_string),_handle(handle)
		{
		}
		bool exec(Filed *entry)
		{
			Filed *basefiled = _table->fs.get(entry->name);
			if(!basefiled)
			{
				return true;
			}
			if(_frist)
			{
				_frist = false;
			}
			else
			{
				query_string << ",";
			}
			query_string << "'" << entry->name << "'" << " = ";
			_handle->storeValue(_table,query_string,basefiled->type,entry->data);
			return true;
		}
	}updcb(table,query_string,this);
	data->execEveryFiled(updcb);
	getWhere(table,query_string,where);
	DWORD ret = (DWORD)-1;
	if(!execSql(query_string.str().c_str(),query_string.str().size()))
	{
		ret = (DWORD)mysql_affected_rows(_mysql);
	}
	if(_update_time.elapse(Time()) >= 3 * 1000L)
	{
		std::ostringstream where_string;
		getWhere(table,where_string,where);
	}
	return ret;
}
DWORD MysqlHandle::exeDelete(const char *tableName,Record *where)
{
	Table *table = pool->tm[_hashcode]->getTableByName(tableName);
	if(!_mysql || !table)
	{
		Test::logger->debug("MysqlHandle::exeDelete error argument is error tableName:%s",tableName);
		return (DWORD)-1;
	}
	_delete_time.now();
	std::ostringstream query_string;
	query_string << "DELETE FROM ";
	query_string << " '" << table->name << " '";
	getWhere(table,query_string,where);
	DWORD ret = (DWORD)-1;
	if(!execSql(query_string.str().c_str(),query_string.str().size()))
	{
		ret = (DWORD)mysql_affected_rows(_mysql);
	}
	return ret;
}
char* MysqlHandle::escapeString(const char *src,char *dest,DWORD size)
{
	if(!src || !dest || !_mysql)
	{
		Test::logger->debug("MysqlHandle::escapeString error argument is error src:%s,dest:%s",src,dest);
		return NULL;
	}
	char *end = dest;
	mysql_real_escape_string(_mysql,end,src,size == 0 ? strlen(src) : size);
	return dest;
}
std::string& MysqlHandle::escapeString(const std::string &src,std::string &dest)
{
	if(!_mysql)
	{
		return dest;
	}
	char buff[2 * src.length() + 1];
	bzero(buff,sizeof(buff));
	mysql_real_escape_string(_mysql,buff,src.c_str(),src.length());
	dest = buff;
	return dest;
}
bool MysqlHandle::escapeString(const std::string &src)
{
	if(!_mysql)
	{
		return false;
	}
	char buff[2 * src.length() + 1];
	bzero(buff,sizeof(buff));
	mysql_real_escape_string(_mysql,buff,src.c_str(),src.length());
	return (strcmp(buff,src.c_str()) == 0);
}
bool MysqlHandle::escapeString(const char *src)
{
	if(!_mysql)
	{
		return false;
	}
	char buff[2 * strlen(src) + 1];
	bzero(buff,sizeof(buff));
	mysql_real_escape_string(_mysql,buff,src,strlen(src));
	return(strcmp(buff,src) == 0);
}
RecordSet* MysqlHandle::exeSelect(const char *tableName,Record *column,Record *where,Record *having,DWORD limit_offset,DWORD limit_rows,Record *groupby,Record *order)
{
	Table *table = pool->tm[_hashcode]->getTableByName(tableName);
	if(!table || !_mysql)
	{
		Test::logger->debug("MysqlHandle::exeSelect error argument is error tableName:%s",tableName);
		return NULL;
	}
	_select_time.now();
	std::ostringstream query_string;
	query_string << "SELECT ";
	if(column && !column->isEmpty())
	{
		struct SqlFiledExec : public EntryCallBack<Filed>
		{
			bool _frist;
			Table *_table;
			std::ostringstream &query_string;
			SqlFiledExec(Table *table,std::ostringstream& query_string):_frist(true),_table(table),query_string(query_string)
			{
			}
			bool exec(Filed *entry)
			{
				if(strncmp(entry->name,"*",strlen(entry->name)) == 0 || _table->fs.get(entry->name))
				{
					if(_frist)
					{
						_frist = false;
					}
					else
					{
						query_string << " , ";
					}
					if(entry->data.empty())
					{
						query_string << "'" << entry->name << "'";
					}
					else
					{
						query_string << (const char *)entry->data;
					}
				}
				return true;
			}
		}sfe(table,query_string);
		column->execEveryFiled(sfe);
	}
	else
	{
		query_string << " * ";
	}
	query_string << " FROM " << " '" << table->name << "' ";
	getWhere(table,query_string,where);
	getGroupBy(table,query_string,groupby);
	getHaving(table,query_string,having);
	getOrder(table,query_string,order);
	if(limit_offset > 0 || limit_rows > 0)
	{
		query_string << " LIMIT " << limit_offset <<  " , " << limit_rows;
	}
	if(execSql(query_string.str().c_str(),query_string.str().size()))
	{
		return NULL;
	}
	DWORD retCount = 0;
	MYSQL_RES *result = NULL;
	result = mysql_store_result(_mysql);
	if(!result)
	{
		return NULL;
	}
	retCount = mysql_num_rows(result);
	if(!retCount)
	{
		return NULL;
	}
	MYSQL_ROW row;
	DWORD num_filed = mysql_num_fields(result);
	MYSQL_FIELD *mysql_fileds = NULL;
	mysql_fileds = mysql_fetch_fields(result);
	RecordSet *ret_set = new RecordSet(retCount);
	if(ret_set)
	{
		DWORD index = 0;
		while((row = mysql_fetch_row(result)))
		{
			QWORD *lengths = mysql_fetch_lengths(result);
			Record *rec = ret_set->get(index++);
			if(rec)
			{
				for(DWORD filedCnt = 0;filedCnt < num_filed;++filedCnt)
				{
					if(row[filedCnt])
					{
						rec->put(mysql_fileds[filedCnt].name,row[filedCnt],lengths[filedCnt]);
					}
				}
			}
		}
	}
	mysql_free_result(result);
	if(ret_set && ret_set->size() == 0)
	{
		DELETE(ret_set);
	}
	return ret_set;
}
struct WhereExec : public EntryCallBack<Filed>
{
	bool _frist;
	Table *_table;
	std::ostringstream &query_string;
	WhereExec(Table *table,std::ostringstream &query_string):_frist(true),_table(table),query_string(query_string)
	{
	}
	bool exec(Filed *entry)
	{
		if(_table->fs.get(entry->name) && entry->data.valid())
		{
			if(_frist)
			{
				_frist = false;
				query_string << " WHERE ";
			}
			else
			{
				query_string << " AND ";
			}
			query_string << (const char *)entry->data;
		}
	}
};
std::ostringstream& MysqlHandle::getWhere(Table *table,std::ostringstream &query_string,Record *where)
{
	if(table && where && !where->isEmpty())
	{
		WhereExec wcb(table,query_string);
		where->execEveryFiled(wcb);
	}
	return query_string;
}
inline std::ostringstream& MysqlHandle::getHaving(Table *table,std::ostringstream &query_string,Record *having)
{
	if(having && !having->isEmpty())
	{
		struct HavingExec : public EntryCallBack<Filed>
		{
			bool _frist;
			Table *_table;
			std::ostringstream &query_string;
			HavingExec(Table *table,std::ostringstream& query_string):_frist(true),_table(table),query_string(query_string)
			{
			}
			bool exec(Filed *entry)
			{
				if(_table->fs.get(entry->name))
				{
					if(_frist)
					{
						query_string << " HAVING ";		
						_frist = false;
					}
					else
					{
						query_string << " AND ";
					}
					query_string << "." << entry->name << "'";
				}
				return true;
			}
		}hcb(table,query_string);
		having->execEveryFiled(hcb);
	}
	return query_string;
}
inline std::ostringstream& MysqlHandle::getGroupBy(Table *table,std::ostringstream &query_string,Record *groupby)
{
	if(groupby && !groupby->isEmpty())
	{
		struct GroupExec : public EntryCallBack<Filed>
		{
			bool _frist;
			Table *_table;
			std::ostringstream &query_string;
			GroupExec(Table *table,std::ostringstream& query_string):_frist(true),_table(table),query_string(query_string)
			{
			}
			bool exec(Filed *entry)
			{
				if(_table->fs.get(entry->name))
				{
					if(_frist)
					{
						query_string << " GROUP BY ";		
						_frist = false;
					}
					else
					{
						query_string << ", ";
					}
					query_string << "." << entry->name << "'";
				}
				return true;
			}
		}gbcb(table,query_string);
		groupby->execEveryFiled(gbcb);
	}
	return query_string;
}
inline std::ostringstream& MysqlHandle::getOrder(Table *table,std::ostringstream &query_string,Record *order)
{
	if(order && !order->isEmpty())
	{
		struct OrderExec : public EntryCallBack<Filed>
		{
			bool _frist;
			Table *_table;
			std::ostringstream &query_string;
			OrderExec(Table *table,std::ostringstream& query_string):_frist(true),_table(table),query_string(query_string)
			{
			}
			bool exec(Filed *entry)
			{
				if(_table->fs.get(entry->name))
				{
					if(_frist)
					{
						query_string << " ORDER BY ";		
						_frist = false;
					}
					else
					{
						query_string << ", ";
					}
					const char *filedValue = entry->data;
					if(strlen(filedValue) == 0)
					{
						query_string << "'" << entry->name << "'";
					}
					else
					{
						query_string << " " << filedValue << " ";
						query_string << " " << entry->name << "'" << " " << filedValue;
					}
				}
				return true;
			}
		}ocb(table,query_string);
		order->execEveryFiled(ocb);
	}
	return query_string;
}
inline std::ostringstream& MysqlHandle::storeValue(Table *table,std::ostringstream &query_string,const SDWORD type, const ValType &value)
{
	switch(type)
	{
		case FIELD_TYPE_STRING:
		case FIELD_TYPE_VAR_STRING:
		case FIELD_TYPE_DATE:
		case FIELD_TYPE_TIME:
		case FIELD_TYPE_DATETIME:
		case FIELD_TYPE_YEAR:
			{
				const char *filedvalue = value;
				DWORD len = strlen(filedvalue);
				char strData[len * 2 + 1];
				mysql_real_escape_string(_mysql,strData,filedvalue,len);
				query_string << "\'" << strData << "\'";
			}
			break;
		case FIELD_TYPE_BLOB:
			{
				DWORD len = value.size();
				if(len)
				{
					char strData[len * 2 + 1];
					mysql_real_escape_string(_mysql,strData,(const char*)value,len);
					query_string << "\'" << strData << "\'";
				}
				else
				{
					query_string << "NULL";
				}
			}
			break;
		default:
			{
				query_string << (const char*)value;
			}
			break;
	}
	return query_string;
}
/*
AutoHandle::AutoHandle(MysqlPool *pool):_pool(pool)
{
	handle = _pool->getHandle();
}
AutoHandle::~AutoHandle()
{
	_pool->putHandle(handle);
}
*/

