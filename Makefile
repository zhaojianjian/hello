pid:pid.o
	gcc -o pid pid.o
pid.o:pid.c
	gcc -c pid.c
clean:
	rm pid.o
