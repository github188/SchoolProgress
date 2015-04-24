######## compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = main.o\
		 global.o\
		 baseLog.o\
		 baseTime.o\
		 basePthread.o\
		 baseEntry.o\
		 baseTest.o\
		 baseTcp.o\
		 baseThread.o\
		 baseSqlTable.o\
		 baseSqlRecord.o\
		 baseSqlHandle.o\
		 baseSqlPool.o\
		 baseTaskThread.o\
		 baseMsgContainer.o\
		 baseEncrypt.o\
		 baseSocket.o

bin/test : $(object)
	$(LINK) -g -lpthread -lrt -lmysqlclient -L/usr/lib/mysql/ -o bin/test $(object) 
main.o : src/main.cpp
	$(CXX) -g -c $< -Iinclude -I/usr/include/mysql/include/
global.o : src/global.cpp
	$(CXX) -g -c $< -Iinclude
baseLog.o : src/baseLog.cpp
	$(CXX) -g -c $< -Iinclude
baseTime.o : src/baseTime.cpp
	$(CXX) -g -c $< -Iinclude
basePthread.o : src/basePthread.cpp
	$(CXX) -g -c $< -Iinclude
baseEntry.o : src/baseEntry.cpp
	$(CXX) -g -c $< -Iinclude
baseTest.o : src/baseTest.cpp
	$(CXX) -g -c $< -Iinclude
baseTcp.o : src/baseTcp.cpp
	$(CXX) -g -c $< -Iinclude -lz
baseThread.o: src/baseThread.cpp
	$(CXX) -g -c $< -Iinclude
baseSqlTable.o : src/baseSqlTable.cpp
	$(CXX) -g -c $< -Iinclude  -I/usr/include/mysql/include/
baseSqlRecord.o : src/baseSqlRecord.cpp
	$(CXX) -g -c $< -Iinclude  -I/usr/include/mysql/include/
baseSqlHandle.o : src/baseSqlHandle.cpp
	$(CXX) -g -c $< -Iinclude  -I/usr/include/mysql/include/
baseSqlPool.o : src/baseSqlPool.cpp
	$(CXX) -g -c $< -Iinclude  -I/usr/include/mysql/include/
baseTaskThread.o : src/baseTaskThread.cpp
	$(CXX) -g -c $< -Iinclude
baseMsgContainer.o : src/baseMsgContainer.cpp
	$(CXX) -g -c $< -Iinclude
baseEncrypt.o : src/baseEncrypt.cpp
	$(CXX) -g -c $< -Iinclude
baseSocket.o : src/baseSocket.cpp
	$(CXX) -g -c $< -Iinclude
clean:
	$(DEL_FILE) $(object)
