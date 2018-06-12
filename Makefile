# the compiler to use
CC = clang++

OBJECTS = main.o sqlite_query.o

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall -std=c++14
  
#files to link:
LDLIBS = -lsqlite3 -lmenu -lncurses
  
all: $(OBJECTS)
	$(CC) $(CFLAGS) -o menu_from_sqlite $(OBJECTS) $(LDLIBS)

clean:
	rm *.o

main.o: src/main.cc src/sqlite_query.h
	$(CC) $(CFLAGS) -c src/main.cc

sqlite_query.o: src/sqlite_query.cc src/sqlite_query.h
	$(CC) $(CFLAGS) -c src/sqlite_query.cc

