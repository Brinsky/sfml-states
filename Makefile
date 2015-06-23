CXX=g++
CXXFLAGS = -Wall -std=c++11

INCLUDES = -I./include -I./include/StateManager
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

vpath %.o ./build
vpath %.h ./include:./include/StateManager
vpath %.cpp ./src:./src/StateManager

all: build libsfml-state-man.a sfml-state-man-test tidy

.PHONY: build clean tidy

libsfml-state-man.a: Game.o GameState.o VirtualScreen.o
	ar rvs $@ $^

sfml-state-man-test: main.cpp Game.o GameState.o VirtualScreen.o ExampleStateA.o ExampleStateB.o
	$(CXX) $^ $(CXXFLAGS) $(LIBS) $(INCLUDES) -o $@

%.o: %.cpp %.h
	$(CXX) -c $< $(CXXFLAGS) $(LIBS) $(INCLUDES)

build:
	if [ ! -d "./build" ]; then mkdir build; fi	

tidy:
	mv -f *.o ./build/

clean:
	rm -f libsfml-state-man.a sfml-state-man-test ./build/*.o
