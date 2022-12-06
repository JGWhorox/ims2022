SHELL = /usr/bin/env bash
NAME = main
LOGIN = 08_xslova21_xgawro00
#---------------
all: 
	g++ -std=c++17 *.cpp -o $(NAME) -lm -lsimlib

zip:
	zip $(LOGIN).zip *.cpp *.h *.pdf Makefile

clean:
	rm -f *.o