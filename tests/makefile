CC = g++
CCFLAGS = -Wall -Werror -std=c++17 -g
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lm
SRC = $(wildcard ../src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TST = $(wildcard *.cpp)
OBJ_TEST = $(filter-out ../src/main.o, $(OBJ)) $(TST:.cpp=.o)
EXEC = testcase.out

all: $(EXEC)

$(EXEC): $(OBJ_TEST)
	$(CC) $^ $(LIBFLAGS) -o $@

%.o: %.cpp
	$(CC) -I ../src -o $@ -c $<

clean:
	rm -f $(OBJ_TEST) $(EXEC)