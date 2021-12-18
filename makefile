CC = g++
CCFLAGS = -Wall -Werror -std=c++17 -g
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lm
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TST = $(wildcard tests/*.cpp)
OBJ_TEST = $(filter-out src/main.o, $(OBJ)) $(TST:.cpp=.o)
EXEC = kayaGUI.out

all: $(EXEC)

#TEST
testcase:
	cd tests; make

#EXEC
$(EXEC): $(OBJ)
	$(CC) $^ $(LIBFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

#CLEAN
cleanall:
	rm -f $(OBJ) $(EXEC)
	cd tests; make clean
clean:
	rm -f $(OBJ) $(EXEC)

cleantest:
	cd tests; make clean