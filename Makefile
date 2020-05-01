#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc
FLAGS=-c -Wall 
LIBS=-lm
OBS=main.o execute.o parse.o socp.o calc.o isjpg.o aviso.c

#Alvo por defeito é o primeiro
all :  soshell

main.o : shell.h main.c
	$(CC) $(FLAGS) main.c -lpthread
execute.o : shell.h execute.c
	$(CC) $(FLAGS) execute.c
parse.o : shell.h parse.c
	$(CC) $(FLAGS) parse.c
calc.o : shell.h calc.c
	$(CC) $(FLAGS) calc.c
isjpg.o : shell.h isjpg.c
	$(CC) $(FLAGS) isjpg.c
socp.o : shell.h socp.c
	$(CC) $(FLAGS) socp.c
aviso.o : shell.h aviso.c
	$(CC) $(FLAGS) aviso.c -lpthread
soshell : $(OBS)
	$(CC)  -o soshell  $(OBS) $(LIBS) -lpthread
clean limpar:
	rm -f soshell *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha" 