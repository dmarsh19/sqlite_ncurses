CXX = clang++
CXXFLAGS = -Wall -std=c++14
LDLIBS = -lsqlite3 -lmenu -lncurses

objects = main.o sqlite_query.o
srcdir := $(CURDIR)/src
executable = menu_from_sqlite

.PHONY: all
all: build

.PHONY: build
build: $(objects)
	$(CXX) $(CXXFLAGS) -o $(executable) $(objects) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(executable) $(objects)

%.o: $(srcdir)/%.cc $(srcdir)/sqlite_query.h
	$(CXX) $(CXXFLAGS) -c $<

