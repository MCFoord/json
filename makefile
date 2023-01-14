CPPFLAGS = -Wall -std=c++17
OBJS = inputhandler.o main.o lexer.o
TESTOBJS = inputhandler.o test.o lexer.o value.o json_object.o

.default: all

all: json.run

clean:
	rm -rf *.o *.dSYM

json.run: $(OBJS)
	g++ $(CPPFLAGS) -g -O -o $@ $^

test.run: $(TESTOBJS)
	g++ $(CPPFLAGS) -g -O -o $@ $^

%.o: %.cpp
	g++ $(CPPFLAGS) -g -c -o $@ $^

.PHONY: all clean

