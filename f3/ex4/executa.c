#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char * argv[], char *envp ){
    char cmd[40];
    
    printf("Introduza o comando\n");
    scanf("%s", cmd);

    if(strcmp(cmd,"port")==0)
        execl(cmd,cmd,NULL);           // variante execl precisa da lista dos comandos

    if(strcmp(cmd,"ingl")==0)
        execl(cmd,cmd,NULL);   

    printf("Não consegui executar a aplicacao.\n");  //só aparece se der erro pois se tudo correr bem a aplicação é bustituida antes que chegar a este ponto     


}
