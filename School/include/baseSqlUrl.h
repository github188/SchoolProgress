#ifndef BASE_SQL_URL_H
#define BASE_SQL_URL_H

#include "baseEntry.h"
#include "baseLock.h"

struct MysqlUrl : public Entry
{
	const DWORD hashcode;
	const std::string url;
	const bool supportTransactions;
	char host[MAX_HOSTSIZE];
	char user[MAX_USERSIZE];
	char passwd[MAX_PASSWORD];
	DWORD port;
	char dbName[MAX_DBSIZE];

	MysqlUrl():hashcode(0),url(),supportTransactions(false)
	{
		bzero(host,sizeof(host));
		bzero(user,sizeof(user));
		bzero(passwd,sizeof(passwd));
		bzero(dbName,sizeof(dbName));
	}

	MysqlUrl(const DWORD hashcode,const std::string &url,const bool supportTransactions = false) : hashcode(hashcode),url(url),supportTransactions(supportTransactions)
	{
		parseMySQLURLString();
	}
 private:
 	void parseMySQLURLString()
	{
		bzero(host,sizeof(host));
		bzero(user,sizeof(user));
		bzero(passwd,sizeof(passwd));
		port=3306;
		bzero(dbName,sizeof(dbName));
		char strPort[16] = "";
		const char *connString = url.c_str();
		if (0 != strncmp(connString,"mysql://",strlen("mysql://")))
			return;
		int j = 0,k = 0;
		for(size_t i = strlen("mysql://"); i < strlen(connString) + 1; i++)
		{
			switch(j)
			{
				case 0:
				{
					if (connString[i] == ':')
					{
						user[k] = '\0'; j++; k = 0;
					}
					else
					{
						user[k++] = connString[i];
					}
					break;
				}
				case 1:
				{
					if (connString[i] == '@')
					{
						passwd[k] = '\0'; j++; k = 0;					 }
					else
					{
						passwd[k++] = connString[i] ;
					}
					break;
				}
				case 2:
				{
					if (connString[i] == ':')
					{
						host[k] = '\0'; j++; k = 0;
					}
					else
					{
						host[k++] = connString[i];
					}
					break;
				}
				case 3:
				{
					if (connString[i] == '/')
					{
						strPort[k] = '\0'; j++; k = 0;
					}
					else
					{
						strPort[k++] = connString[i];
					}
					break;
				}
				case 4:
				{
					if (connString[i] == '\0')
					{
						dbName[k] = '\0'; j++; k = 0;
					}
					else
					{
						dbName[k++] = connString[i];
					}
					break;
				}
				default:
					break;
			}
		}
		port=atoi(strPort);
	}
};
class MysqlUrlManager : public EntryManager<EntryID,EntryNone<2>,EntryNone<3> >
{
	public:
		MysqlUrlManager()
		{
		}
		~MysqlUrlManager()
		{
			deleteAll();
		}
		bool addMysqlUrl(MysqlUrl *entry)
		{
			bool bret = false;
			rwlock.wrlock();
			bret = addEntry(entry);
			rwlock.unlock();
			return bret;
		}
		void removeMysqlUrl(MysqlUrl *entry)
		{
			rwlock.wrlock();
			removeEntry(entry);
			rwlock.unlock();
		}
		MysqlUrl *getMysqlUrlByID(const DWORD hashcode)
		{
			MysqlUrl *ret = NULL;
			rwlock.rdlock();
			ret = (MysqlUrl*)getEntryByID(hashcode);
			return ret;
		}
		template<class YourEntry>
		bool execEveryMysqlUrl(EntryCallBack<YourEntry> &exec)
		{
			rwlock.rdlock();
			bool ret = execEveryEntry(exec);
			rwlock.unlock();
			return ret;
		}
	private:
		RWLock rwlock;
};



#endif


