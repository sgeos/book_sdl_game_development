CXX = clang++
SDL_HEADER = /opt/local/include
SDL_LIB = /opt/local/lib
SDL = -lSDL2 -lSDL2_image -lSDL2_ttf -L$(SDL_LIB)
CXXFLAGS = -Wall -c -std=c++14 -I$(SDL_HEADER)
LDFLAGS = $(SDL)
EXE = ../bin/Chapter3

.PHONY: all
all: $(EXE)

$(EXE): main.o Constants.o Enemy.o Game.o LoaderParams.o Log.o Player.o SdlGameObject.o TextureManager.o
	$(CXX) $(LDFLAGS) $^ -o $@

.o: .cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run
run: $(EXE)
	$(EXE)

.PHONY: clean
clean:
	rm -rf *.o $(EXE)

