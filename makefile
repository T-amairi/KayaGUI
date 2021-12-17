CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 
SRC = $(wildcard src/*.cc)
OBJ = $(SRC:.cc=.o)
TST = $(wildcard tests/*.cc)
OBJ_TEST = $(filter-out src/main.o, $(OBJ)) $(TST:.cc=.o)

all: kayaGUI

testcase:
	cd tests; make

kayaGUI: $(OBJ)
	$(CC) $^ $(LIBFLAGS) -o $@

%.o: %.cc
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) kayaGUI

cleantest:
	cd tests; make clean