all: compiler

compiler:
	g++ -o compiler main.cpp
clean:
	rm -f compiler
	rm -f out.*
	rm -f *.out
	rm -f *.preorder
	rm -f *.asm
