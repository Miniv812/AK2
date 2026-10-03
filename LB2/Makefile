CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

LIB_NAME = libcalculator.a
EXEC_NAME = calculator_app

LIB_OBJS = calculator.o
MAIN_OBJ = main.o

all: $(EXEC_NAME)

$(LIB_NAME): $(LIB_OBJS)
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC_NAME): $(MAIN_OBJ) $(LIB_NAME)
	$(CXX) $(CXXFLAGS) $(MAIN_OBJ) -L. -lcalculator -o $@

clean:
	rm -f *.o $(LIB_NAME) $(EXEC_NAME)

.PHONY: all clean
