#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <math.h>
#include <dirent.h>

typedef struct{
    char msg[100];
    int tempo;
}aviso_t;

typedef struct{ 
    char fonte[100];
    char destino[100]; 
    int buffsize;
}copiar_t;

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin (char **args);

int socp(char *fonte, char *destino, int BLOCKSIZE);

void ioCopy(int IN,int OUT);

void calcula(char *v1, char *op, char *v2);

void bits( char *op1, char *op, char *op2);

int isjpg(int fileDescriptor);

void verifica(char *nomeFile);

void aviso(char *mesg, int tempo);

void *avisowrapper(void *args);

void *socpth(void *args);

int biggestFile(char *file1, char *file2);

void setRunPerm(char *file);

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1
