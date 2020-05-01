#include "shell.h"

void calcula(char *v1, char *op, char *v2){
    float a=atof(v1);
    float b=atof(v2);
    
    if(strcmp(op,"+")==0){ //soma
        printf("Resultado: %f\n",a+b);
        return;
    }

    if(strcmp(op,"-")==0){ //subtração
        printf("Resultado: %f\n",a-b);
        return;
    }

    if(strcmp(op,"*")==0){ //multiplicação
        printf("Resultado: %f\n",a*b);
        return;
    }

    if(strcmp(op,"/")==0){ //divisão
        if(b==0){
            perror("Impossivel a divisão por zero!!!");
            return;
        }

        printf("Resultado: %f\n",a/b);
        return;
    }

    if(strcmp(op,"^")==0){
        printf("Resultado: %f\n",powf(a,b));
        return;
    }

    printf("Operation %s does not exist!!!\n",op);
}

void bits( char *op1, char *op, char *op2){
    int a=atoi(op1);
    int b=atoi(op2);

    if(strcmp(op,"&")==0){ //AND
        printf("Resultado: %d\n",a&b);
        return;
    }

    if(strcmp(op,"^")==0){ //exclusive OR
        printf("Resultado: %d\n",a^b);
        return;
    }

    if(strcmp(op,"|")==0){ //inclusive OR
        printf("Resultado: %d\n",a|b);
        return;
    }

    printf("Operation %s does not exist!!!\n",op);
    return;
}