CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 
SRC = $(wildcard $(../src)/*.cc)
OBJ = $(SRC:.cc=.o)
TST = $(wildcard *.cc)
OBJ_TEST = $(filter-out $(../src)/main.o, $(OBJ)) $(TST:.cc=.o)

all: testcase

testcase: $(OBJ_TEST)
	$(CC) $^ $(LIBFLAGS) -o $@

%.o: %.cc
	$(CC) -I$(../src) -o $@ -c $<

clean:
	rm -f $(OBJ_TEST) testcase