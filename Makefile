SHELL = /usr/bin/env bash
NAME = genevachecklist
LOGIN = xgawro00
#---------------
all: 
	g++ -std=c++17 *.cpp -o $(NAME) -lm -lsimlib

zip:
	tar -cvf $(LOGIN).tar *.cpp *.h *.pdf Makefile

clean:
	rm -f *.o