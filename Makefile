
all:
	g++ -Isrc/include -Lsrc/lib -o main main.cpp board.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
run:
	chmod +x main
	./main
clean:
	rm -rf *.o main