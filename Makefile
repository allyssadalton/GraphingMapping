CC=g++
CFLAGS=-c -Wall -ggdb -I. -std=c++17 -O1 -pg -g
LDFLAGS=-pg
SOURCES=MyGraph.cpp MyGraph-sandbox.cpp
EXECUTABLE=MyGraph
TESTS=MyGraph.cpp MyGraph_test.cpp


#TODO: Need a more elegant way of specifying objects and tests
GTESTDIR=$$(pwd)/googletest
OBJECTS=$(SOURCES:.cpp=.o)

FLAGS   = -Iinclude 

all: $(SOURCES) $(EXECUTABLE)
	

# These next lines do a bit of magic found from http://stackoverflow.com/questions/2394609/makefile-header-dependencies
# Essentially it asks the compiler to read the .cpp files and generate the needed .h dependencies.
# This way if any .h file changes the correct .cpp files will be recompiled
depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend
# End .h file magic

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	cp $(EXECUTABLE) a.out

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE) test_executable a.out
	rm -rf coverage
	rm -f ./.depend
	rm $(GTESTDIR)/libgtest.a
	rm $(GTESTDIR)/gtest-all.o
	

# Google test section
$(GTESTDIR)/libgtest.a: 
	$(CC) -isystem $(GTESTDIR) -I $(GTESTDIR) -pthread -c $(GTESTDIR)/src/gtest-all.cc -o $(GTESTDIR)/gtest-all.o -std=c++17
	ar -rv $(GTESTDIR)/libgtest.a $(GTESTDIR)/gtest-all.o

# This will also recompile if any source file is changed.
test_executable: $(GTESTDIR)/libgtest.a $(TESTS) depend
	$(CC) -isystem $(GTESTDIR) -pthread -std=c++17 -ggdb $(TESTS) $(GTESTDIR)/src/gtest_main.cc $(GTESTDIR)/libgtest.a -o test_executable

test_all: test_executable
	./test_executable --gtest_print_time=0

test: test_executable
	./test_executable --gtest_print_time=0 --gtest_filter=-*Dykstras*.*:*BellmanFord*.*
	
coverage: test_executable
	rm -rf coverage
	mkdir coverage
	kcov --include-pattern=MyHash.cpp coverage/ ./test_executable
	firefox coverage/test_executable/index.html &
