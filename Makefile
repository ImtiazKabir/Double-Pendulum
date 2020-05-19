all:
	g++ -c -Wall -Wextra main.cpp

sfml:
	g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

