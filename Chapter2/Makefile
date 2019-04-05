CXX = clang++
SDL_HEADER = /opt/local/include
SDL_LIB = /opt/local/lib
SDL = -lSDL2 -L$(SDL_LIB)
CXXFLAGS = -Wall -c -std=c++14 -I$(SDL_HEADER)
LDFLAGS = $(SDL)
EXE = ../bin/Chapter2

.PHONY: all
all: $(EXE)

$(EXE): main.o Constants.o Game.o Log.o
	$(CXX) $(LDFLAGS) $^ -o $@

.o: .cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run
run: $(EXE)
	$(EXE)

.PHONY: clean
clean:
	rm -rf *.o $(EXE)

