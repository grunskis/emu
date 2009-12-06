test: 8080.o test.o
	@gcc -g -o test test.o 8080.o

8080.o: 8080.c 8080.h
	@gcc -g -c -o 8080.o 8080.c

test.o: test.c
	@gcc -g -c -o test.o test.c

.PHONY: clean

clean:
	@rm -f *.o test
