all:
	g++ src/*.cpp -I include/ -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm a.out
