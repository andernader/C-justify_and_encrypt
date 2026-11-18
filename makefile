Caesar_Cipher: main.o line.o words.o
	gcc -o Caesar_Cipher main.o line.o words.o
main.o: main.c line.h words.h debug_f.h
	gcc -c main.c
line.o: line.c line.h words.h debug_f.h
	gcc -c line.c
words.o: words.c words.h debug_f.h
	gcc -c words.c