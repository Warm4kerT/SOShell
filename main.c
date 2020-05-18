#include "shell.h"

char prompt[100];

int main ()
{
  int len;
  char linha[1024];/* um comando */
  char *args[64];/* com um maximo de 64 argumentos */

  strcpy (prompt, "SOSHELL: Introduza um comando : prompt>");
  while (1)
  {
    printf ("%s", prompt);
    if (fgets (linha, 1023, stdin) == NULL)
    {
      printf("\n");
      exit(0);
    }
    len = strlen (linha);
    if (1 == len)
      continue;/* linha é apenas \n */
    
    if (linha[len-1]=='\n')
      linha[len-1] = '\0';
    
    int numargs=parse(linha, args);/* particiona a string em argumentos */

    if (!builtin (args))
      execute(numargs, args);/* executa o comando */
    }
  return 0;
}

int builtin (char **args)
{
  if (strcmp (args[0], "sair") == 0)/*Sair da Shell*/
  {
    exit(0);
    return 1;
  }

  if (strncmp (args[0], "42", 2) == 0) /*EasterEgg*/
  {
    printf ("42 is the answer to life the universe and everything\n");
    return 1;/* funcionalidade embutida */
  }

  if (strcmp(args[0],"obterinfo") == 0){ /*Obter Info sobre a shell*/
    printf("SOShell 2020 versão 1.0\n");
    return 1;
  }

  if (strlen(args[0])>4 && 0==strncmp(args[0], "PS1=",4) ){ /*Mudança do prompt*/
    strcpy(prompt,args[0]+4);
    return 1 ; //comando embutido
  }

  if (strcmp(args[0], "quemsoueu") == 0){/* User info*/
    system("id");
    return 1;
  }

  if (strcmp(args[0],"cd") == 0){ /*cd change directory*/
    int err;
    
    if(NULL == args[1] || strcmp(args[1],"~") == 0){
      err=chdir(getenv("HOME"));
    }else{
      err=chdir(args[1]);
    }

    if(err<0)
      perror(args[1]);
    
    return 1;
  }

  if (strcmp(args[0],"calc") == 0){
   if(args[4]!=NULL){
      perror("Too many arguments!!!");
      return 2;
    }

    if(args[1]==NULL||args[2]==NULL||args[3]==NULL){
      perror("Missing arguments!!!");
      return 2;
    }

    calcula(args[1],args[2],args[3]);
    
    return 1;
  }

  if (strcmp(args[0],"bits") == 0){
   if(args[4]!=NULL){
      perror("Too many arguments!!!");
      return 2;
    }

    if(args[1]==NULL||args[2]==NULL||args[3]==NULL){
      perror("Missing arguments!!!");
      return 2;
    }

    bits(args[1],args[2],args[3]);
    
    return 1;
  }

  if (strcmp(args[0],"isjpg") == 0){
   if(args[2]!=NULL){
      perror("Too many arguments!!!");
      return 2;
    }

    if(args[1]==NULL){
      perror("Missing arguments!!!");
      return 2;
    }

    verifica(args[1]);
    
    return 1;
  }

  if(strcmp(args[0],"avisoTeste")==0){
    aviso(args[1],atoi(args[2]));
    return 1;
  }

  if(strcmp(args[0],"aviso")==0){
    pthread_t th;
    aviso_t *ptr=(aviso_t *)malloc(sizeof(aviso_t));
    strcpy(ptr->msg, args[1]);
    ptr->tempo=atoi(args[2]);
    pthread_create(&th, NULL, avisowrapper,(void *)ptr);
    return 1;
  }

  if (strcmp(args[0],"socp") == 0){ /*file copy*/
    if(args[3]!=NULL){
      socp(args[1],args[2],atoi(args[3]));
    }else{
      socp(args[1],args[2],128);
    }
    return 1;
  }
  
  if (strcmp(args[0],"socpth") == 0){ /*file copy*/
    pthread_t th;
    copiar_t *cp=(copiar_t *)malloc(sizeof(copiar_t));
    strcpy(cp->fonte, args[1]);
    strcpy(cp->destino, args[2]);
    
    if(args[3]!=NULL){
      cp->buffsize=atoi(args[3]);
    }else{
      cp->buffsize=128;
    }
    
    pthread_create(&th, NULL, socpth,(void *)cp);
    return 1;
  }

  if (strcmp(args[0],"maior") == 0){
    
    if(args[1]!=NULL && args[2]!=NULL){
      biggestFile(args[1],args[2]);
    }else{
      perror("Input error!!\n");
    }
    
    return 1;
  }

  /* IMPORTANTE : e
   Devolver 0 para indicar que não existe comando embutido e que
   será executado usando exec() na função execute.c
  */
  return 0;
}
