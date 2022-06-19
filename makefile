all:
	g++ -Isrc/include -Lsrc/lib -o STARFIELD *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_gfx -lSDL2_ttf