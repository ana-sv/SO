ex3: programa.o imprime.o
	gcc progrma.o imprime.o -o ex3

programa.o: programa.c imprime.h
	gcc programa.c -c

imprime.o: imprime.c
	gcc impriem.c -c

limpa:
	rm *.o 
