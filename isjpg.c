#include "shell.h"

int isjpg(int fileDescriptor);

void verifica(char *nomeFile){
    int file=open(nomeFile,O_RDWR);
    if(file<0){
        perror("File does not exist!!!");
        return;
    }

    if(isjpg(file)==1){
        printf("O ficheiro %s é um JPG\n",nomeFile);
    }else{
        printf("O ficheiro %s não é um JPG\n",nomeFile);
    }

}

int isjpg(int fileDescriptor){ //esboço da função
    unsigned char b[4];
    read(fileDescriptor,b,4);
    
    //voltar ao inicio do ficheiro com lseek
    if ( b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0)
        return 1;
    return 0;
}