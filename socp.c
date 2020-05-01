#include "shell.h"

int BUFFSIZE;

void ioCopy(int IN,int OUT);

int socp(char *fonte, char *destino, int BLOCKSIZE){

    BUFFSIZE=BLOCKSIZE;

    if(fonte==destino && fonte==NULL){
        ioCopy(STDIN_FILENO,STDOUT_FILENO);
        return 0; 
    }

    int fdIn=open(fonte,O_RDONLY);
    if(fdIn<0){
        perror("No File Found!!!");
        return 0;
    }
    
    int fdOut=open(destino,O_RDWR);
    if(fdOut<0){
        fdOut=open(destino,O_CREAT,0666);
        fdOut=open(destino,O_RDWR);
    }
    
    ioCopy(fdIn,fdOut);
    
    return(0);
}
    

void ioCopy(int IN,int OUT){

    int n;
    clockid_t inicio, fim;
    float tempoUsado;

    char *buf=malloc(BUFFSIZE);
    inicio=clock();

    while((n=read(IN,buf,BUFFSIZE))>0){
        if(write(OUT, buf,n)!=n){
            perror("Erro de escrita!\n");
            break;
        }
    }
    
    fim=clock();
    tempoUsado=(float)(fim-inicio)/(float) CLOCKS_PER_SEC;

    if(n <0){
        perror("Erro de leitura!\n");
    }else{
        fprintf( stderr, "Copia Feita com BlockSize %d Tempo do CPU %f\n", BUFFSIZE, tempoUsado);
    }
}

void *socpth(void *args){
    copiar_t *cp=(copiar_t *)args;
    socp(cp->fonte,cp->destino,cp->buffsize);
    free(cp);
    return NULL;
}