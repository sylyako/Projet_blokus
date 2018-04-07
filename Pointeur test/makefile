PROG = partie
OBJ = menu_accueil.o afficher.o init_plateau.o unicode.o
CC = gcc
CFLAGS = -g -W


prog: ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${PROG}

menu_accueil.o : menu_accueil.c
	${CC} ${FLAGS} -c menu_accueil.c

afficher.o : afficher.c
	${CC} ${FLAGS} -c afficher.c

init_plateau.o : init_plateau.c
	${CC} ${FLAGS} -c init_plateau.c
	
unicode.o : unicode.c
	${CC} ${FLAGS} -c unicode.c

all: prog
	
clean :
	- rm  *.o
	- rm  partie