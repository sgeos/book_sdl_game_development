CXX = clang++
LLDB = lldb
SDL_HEADER = /opt/local/include
SDL_LIB = /opt/local/lib
SDL = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L$(SDL_LIB)
CXXFLAGS = -g -Wall -c -std=c++14 -I$(SDL_HEADER)
LDFLAGS = $(SDL)
LLDBFLAGS =
LIBZ_DIR = ../zlib-1.2.11/
EXE = ../bin/Chapter8

.PHONY: all
all: $(EXE)

$(EXE): base64.o main.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o AnimatedGameObject.o BulletHandler.o CollisionManager.o Constants.o DemoBackground.o DemoBackgroundObject.o DemoGameObject.o DemoPlayer.o DemoState.o Game.o GameObjectFactory.o GameOverState.o GameStateMachine.o InputHandler.o Level.o LevelParser.o LoaderParams.o Log.o MainMenuState.o MenuButton.o MenuState.o ObjectLayer.o PauseState.o Player.o PlayState.o ScrollingBackground.o ShooterObject.o SoundManager.o StateParser.o TextureManager.o TileLayer.o libz.a
	mkdir -p $$(dirname $@)
	$(CXX) $(LDFLAGS) $^ -o $@

.o: .cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

libz.a:
	cd $(LIBZ_DIR) && ./configure --static
	$(MAKE) -C $(LIBZ_DIR)
	cp $(LIBZ_DIR)/zlib.h $(LIBZ_DIR)/zconf.h $(LIBZ_DIR)/libz.a .

.PHONY: run
run: $(EXE)
	$(EXE)

.PHONY: debug
debug: $(EXE)
	$(LLDB) $(LLDBFLAGS) $(EXE)

.PHONY: clean
clean:
	rm -rf *.o *.a $(EXE)

