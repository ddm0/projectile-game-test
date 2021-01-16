all: m
	./a.out

m:
	g++ src/*.cpp -I include/ -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system

r:
	./a.out

clean:
	rm a.out
