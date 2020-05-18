#include "shell.h"
int biggestFile(char *file1, char *file2){
    struct stat stats;
    int size1, size2;

    if(stat(file1, &stats)==0){
        size1=stats.st_size;
    }else{
        perror("Error opening file1\n");
        return 0;
    }

    if(stat(file2, &stats)==0){
        size2=stats.st_size;
    }else{
        perror("Error opening file2\n");
        return 0;
    }

    if(size1==size2){
        printf("Same size files: %d\n",size1);
    }else{
        if(size1>size2){
            printf("Biggest File: %s\t%d\n",file1,size1);
        }else{
            printf("Biggest File: %s\t%d\n",file2,size2);
        }
    }
    
    return 0;
}

void setRunPerm(char *file){
    if(chmod(file, S_IXUSR)==0){
        printf("Sucesseful\n");
    }else{
        perror("Error\n");
    }
}