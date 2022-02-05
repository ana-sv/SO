// Ana Videira - 2015012218 
// Sistemas Operativos 2021/2022


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char * argv[], char *envp ){


    char cmd[40];
    
    printf("Introduza o comando\n");
    scanf("%s", cmd);
    
    execl(cmd,cmd,NULL);           // variante execl precisa da lista dos comandos


    /*
    char cmd[40];
    char *args[]={cmd,NULL};

    printf("Introduza o comando\n");
    scanf("%s", cmd);
    execvp(args[0], args);  

    */


    printf("Não consegui executar a aplicacao.\n");  //só aparece se der erro pois se tudo correr bem a aplicação é bustituida antes que chegar a este ponto     


}




/*

execlp and execl : These two also serve the same purpose but the syntax of them are a bit different which is as shown below:
 Syntax:

int execlp(const char *file, const char *arg, ...  (char  *) NULL );
int execl(const char *path, const char *arg, ...  (char  *) NULL );


*/