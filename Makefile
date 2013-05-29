tudo: alg3
alg3: aplic1.o aplic2.o bs-tree.o
	gcc -lm -o aplic1 aplic1.o bs-tree.o
	gcc -lm -o aplic2 aplic2.o bs-tree.o


aplic1.o: aplic1.c
	gcc -c aplic1.c
aplic2.o: aplic2.c
	gcc -c aplic2.c
bs-tree.o: bs-tree.c bs-tree.h
	gcc -c bs-tree.c
limpa:
	rm -f *.o *.~* *.bak core*
