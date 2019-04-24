CXX = clang++
LLDB = lldb
SDL_HEADER = /opt/local/include
SDL_LIB = /opt/local/lib
SDL = -lSDL2 -L$(SDL_LIB)
CXXFLAGS = -g -Wall -c -std=c++14 -I$(SDL_HEADER)
LDFLAGS = $(SDL)
LLDBFLAGS =
EXE = ../bin/Chapter1

.PHONY: all
all: $(EXE)

$(EXE): main.o Constants.o Game.o Log.o
	mkdir -p $$(dirname $@)
	$(CXX) $(LDFLAGS) $^ -o $@

.o: .cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run
run: $(EXE)
	$(EXE)

.PHONY: debug
debug: $(EXE)
	$(LLDB) $(LLDBFLAGS) $(EXE)

.PHONY: clean
clean:
	rm -rf *.o $(EXE)

