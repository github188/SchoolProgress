####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = memTset.o
		 
bin/memTset : $(object)
	$(LINK) -g -o bin/memTset $(object) -I /usr/local/include/libxml2/ -L /usr/local/include/lib/ -lssl -lcrypto -lxml2 -levent -lmemcached -luuid	
	
memTset.o : memTset.cpp
	$(CXX) -g -c $< -Iinclude
clean:
	$(DEL_FILE) $(object) bin/memTset
