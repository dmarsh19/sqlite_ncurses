CXX = clang++

OBJECTS = main.o sqlite_query.o

CXXFLAGS = -Wall -std=c++14
  
LDLIBS = -lsqlite3 -lmenu -lncurses
  
all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o menu_from_sqlite $(OBJECTS) $(LDLIBS)

clean:
	rm *.o

main.o: src/main.cc src/sqlite_query.h
	$(CXX) $(CXXFLAGS) -c src/main.cc

sqlite_query.o: src/sqlite_query.cc src/sqlite_query.h
	$(CXX) $(CXXFLAGS) -c src/sqlite_query.cc

