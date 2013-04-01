####### Compiler, tools and options

DEL_FILE      = rm -f
CC            = gcc
CXX           = g++
LINK          = g++

####### Files
object = numStr.o\
		 main.o
	
bin/test : $(object)
	$(LINK) -g -o bin/test $(object) 
	
numStr.o : src/numStr.cpp
	$(CXX) -g -c $< -Iinclude

main.o : src/main.cpp
	$(CXX) -g -c $< -Iinclude

clean:
	$(DEL_FILE) $(object)
