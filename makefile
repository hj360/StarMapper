all:
	g++ -Isrc/include -IDATA -IGUI -Lsrc/lib -o STARMAPPER *.cpp DATA/*.cpp GUI/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_gfx -lSDL2_ttf