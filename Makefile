

all: mini-shell

mini-shell: main.o mon_shell.o lire.o execute_pipe.o
	gcc  -o mini-shell  main.o mon_shell.o lire.o execute_pipe.o

main.o: main.c mon_shell.h
	gcc -c main.c

mon_shell.o: mon_shell.c lire.h execute_pipe.h
	gcc  -c mon_shell.c

lire.o: lire.c
	gcc  -c lire.c

execute_pipe.o: execute_pipe.c lire.h
	gcc  -c execute_pipe.c

clean:
	rm mini-shell
	rm *.o
