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
        printf("Same size files: %d\n",size1/1024);
    }else{
        if(size1>size2){
            printf("Biggest File: %s\t%d\n",file1,size1/1024);
        }else{
            printf("Biggest File: %s\t%d\n",file2,size2/1024);
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

void remReadPerm(char *file){
    if(chmod(file, S_IRWXU | S_IWGRP | S_IXGRP | S_IWOTH| S_IXOTH)==0){
        printf("Sucesseful\n");
    }else{
        perror("Error changing perm!!!\n");
    }
}

void sols(char *path){
    DIR *dp;
    struct dirent *direct;
    struct stat aux;

    if((dp=opendir(path))==NULL){
        closedir(dp);
        perror("Can't open directory!!!\n");
        return;
    }

    printf("\nName\t\t  Inode\t\t\tSize\n\n");

    while((direct=readdir(dp))!=NULL){
        stat(direct->d_name,&aux);
        printf("%s\t\t  %ld\t%ld Bytes\n",direct->d_name,direct->d_ino,aux.st_size);
    }
}