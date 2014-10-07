#ifndef BASE_MSG_CONTAINER_H
#define BASE_MSG_CONTAINER_H
#include <iostream>
#include <string.h>
#include <vector>
#include <assert.h>
#include <queue>
#include <ext/pool_allocator.h>
#include "baseDef.h"
#include "baseCmd.h"
using namespace std;

const DWORD trunkSize = 64 * 1024;

#define trunkCount(size)(((size) + trunkSize - 1) / trunkSize)

#define unzip_size(zip_size)((zip_size) * 120 / 100 + 12)

const DWORD PACKET_ZIP_BUFFER = unzip_size(trunkSize - 1) + sizeof(DWORD) + 8;
template<typename _type>
class ByteBuffer
{
	private:
		DWORD _maxSize;
		DWORD _offPtr;
		DWORD _curPtr;
		_type _buffer;
	public:
		ByteBuffer();
		inline void put(const BYTE *buf,const DWORD size)
		{
			wr_reserve(size);
			bcopy(buf,&_buffer[_curPtr],size,size);
			_curPtr += size;
		}

		inline BYTE *wr_buf()
		{
			return &_buffer[_curPtr];
		}
		inline BYTE *rd_buf()
		{
			return &_buffer[_offPtr];
		}
		inline bool rd_ready()
		{
			return _curPtr > _offPtr;
		}
		inline DWORD rd_size()
		{
			return _curPtr - _offPtr;
		}
		inline void rd_flip(const DWORD size)
		{
			if(!size) return;
			_offPtr += size;
			if(_curPtr > _offPtr)
			{
				DWORD tmp = _curPtr - _offPtr;
				if(tmp <= _offPtr)
				{
					memmove(&_buffer[0],&_buffer[_offPtr],tmp);
					_offPtr = 0;
					_curPtr = tmp;
				}
			}
			else
			{
				_offPtr = 0;
				_curPtr = 0;
			}
		}
		inline DWORD wr_size()
		{
			return _maxSize - _curPtr;
		}
		inline void wr_flip(const DWORD size)
		{
			_curPtr += size;
		}
		inline void reset()
		{
			_offPtr = 0;
			_curPtr = 0;
		}
		inline const DWORD maxSize() const
		{
			return _maxSize;
		}
		inline void wr_reserve(const DWORD size);
};

typedef ByteBuffer<std::vector<BYTE> > t_BufferCmdQueue;


template<>
void t_BufferCmdQueue::wr_reserve(const DWORD size)
{
	if(wr_size() < size)
	{
		_maxSize += trunkSize * trunkCount(size+8);
		_buffer.resize(_maxSize);
	}
}


typedef ByteBuffer<BYTE [PACKET_ZIP_BUFFER]> t_StackCmdQueue;


///栈不能动态扩增
template<>
void t_StackCmdQueue::wr_reserve(const DWORD size)
{
	assert(wr_size() >= size);

}

template<typename Cmd_type,DWORD size = 64 * 1024>
class CmdBuffer_wrapper
{
	public:
		typedef Cmd_type type;
		DWORD cmd_size;
		DWORD max_size;
		type* cnt;
		CmdBuffer_wrapper():cmd_size(sizeof(type)),max_size(size)
		{
			cnt = (type*)buffer;
			constructInPlace(cnt);
		}
	private:
		BYTE buffer[size];
};

class Processor
{
	public:
		virtual bool msgParse(const Cmd::t_NullCmd *cmd,const DWORD length) = 0;
		virtual bool msgParseStart(const Cmd::t_NullCmd *cmd,const DWORD length) = 0;
		virtual bool msgParseForward(const Cmd::t_NullCmd *cmd,const DWORD length) = 0;
};
typedef std::pair<DWORD,BYTE*> CmdPair;
#define QueueSize 102400
class MsgQueue
{
	public:
		MsgQueue()
		{
			queueRead = 0;
			queueWrite = 0;
		}
		~MsgQueue()
		{
			clear();
		}
		typedef std::pair<volatile bool,CmdPair> CmdQueue;
		CmdPair* get()
		{
			CmdPair *ret = NULL;
			if(cmdQueue[queueRead].first)
			{
				ret = &cmdQueue[queueRead].second;
			}
			return ret;
		}
		void erase()
		{
			free(cmdQueue[queueRead].second.second);
			cmdQueue[queueRead].first = false;
			queueRead = (++queueRead) % QueueSize;
		}
		bool put(const void *ptNullCmd,const DWORD cmdLen)
		{
			BYTE *buf = (BYTE*)malloc(cmdLen + 1);
			if(buf)
			{
				bcopy(ptNullCmd,buf,cmdLen);
				if(!putQueueToArray() && !cmdQueue[queueWrite].first)
				{
					cmdQueue[queueWrite].second.first = cmdLen;
					cmdQueue[queueWrite].second.second = buf;
					cmdQueue[queueWrite].first = true;
					queueWrite = (++queueWrite) % QueueSize;
					return true;
				}
				else
				{
					queueCmd.push(std::make_pair(cmdLen,buf));
				}
				return true;
			}
			return false;
		}
	private:
		void clear()
		{
			while(putQueueToArray())
			{
				while(get())
				{
					erase();
				}
			}
			while(get())
			{
				erase();
			}
		}
		bool putQueueToArray()
		{
			bool isLeft = false;
			while(!queueCmd.empty())
			{
				if(!cmdQueue[queueWrite].first)
				{
					cmdQueue[queueWrite].second = queueCmd.front();
					cmdQueue[queueWrite].first = true;
					queueWrite = (++queueWrite) % QueueSize;
					queueCmd.pop();
				}
				else
				{
					isLeft = true;
					break;
				}
			}
			return isLeft;
		}
	//	__gnu_cxx::__mt_alloc<BYTE>  __mt_alloc;
		CmdQueue cmdQueue[QueueSize];
	//	std::queue<CmdPair,std::deque<CmdPair,__gnu_cxx::_pool_alloc<CmdPair> > >queueCmd;
		std::queue<CmdPair>queueCmd;
		DWORD queueWrite;
		DWORD queueRead;
};
				

//template<bool lock=false>
class MessageQueue : /*public RWLocker<lock>,*/public Processor
{
	protected:
		virtual ~MessageQueue()
		{
		}
	public:
		bool cmdMsgParse(const Cmd::t_NullCmd *ptNullCmd,const DWORD cmdLen)
		{
		//	RWLocker<lock>::wrlock();
			bool bret = cmdQueue.put((void*)ptNullCmd,cmdLen);
		//	RWLocker<lock>::unlock();
			return bret;
		}
		bool doCmd()
		{
		//	RWLocker<lock>::wrlock();
			CmdPair *cmd = cmdQueue.get();
			while(cmd)
			{
				const Cmd::t_NullCmd *ptNullCmd = (const Cmd::t_NullCmd*)cmd->second;
				/*
				switch(ptNullCmd->byCmd)
				{
					case Cmd::Server::START_SERVERCMD:
						{
							msgParseStart(ptNullCmd,cmd->first);
						}
						break;
					case Cmd::Server::FORWARD_SERVERCMD:
						{
							msgParseForward(ptNullCmd,cmd->first);
						}
						break;
					default:
						{
							msgParse(ptNullCmd,cmd->first);
						}
						break;
				}
				*/
			cmdQueue.erase();
			cmd = cmdQueue.get();
		}
		if(cmd)
		{
			cmdQueue.erase();
		}
	//	RWLocker<lock>::unlock();
		return true;
	}
private:
	MsgQueue cmdQueue;
};


#endif
