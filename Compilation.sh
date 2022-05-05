gcc -c Position.c
gcc -c Joueur.c
gcc -c Tablette.c
gcc -c Main.c
gcc Main.o Position.o Tablette.o Joueur.o -ansi -Wall -pedantic -lncurses