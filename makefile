iCarrom:main.cpp
	g++ main.cpp Game.cpp Coin.cpp Object.cpp Board.cpp TextureLoader.cpp MainMenu.cpp ScreenManager.cpp   -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o iCarrom

clean:
	rm -rf *o iCarrom
        
