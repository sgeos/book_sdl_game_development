CXX = clang++
SDL_HEADER = /opt/local/include
SDL_LIB = /opt/local/lib
SDL = -lSDL2 -lSDL2_image -lSDL2_ttf -L$(SDL_LIB)
CXXFLAGS = -Wall -c -std=c++14 -I$(SDL_HEADER)
LDFLAGS = $(SDL)
EXE = ../bin/Chapter6

.PHONY: all
all: $(EXE)

$(EXE): main.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o AnimatedGameObject.o Constants.o DemoBackground.o DemoBackgroundObject.o DemoGameObject.o DemoPlayer.o DemoState.o Enemy.o Game.o GameOverState.o GameStateMachine.o InputHandler.o LoaderParams.o Log.o MenuButton.o MenuState.o PauseState.o Player.o PlayState.o SdlGameObject.o TextureManager.o
	$(CXX) $(LDFLAGS) $^ -o $@

.o: .cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: run
run: $(EXE)
	$(EXE)

.PHONY: clean
clean:
	rm -rf *.o $(EXE)
