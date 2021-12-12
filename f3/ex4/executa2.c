#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
- quando fazemos execl no codigo "estragamos" no 1 codigo pois este é substituido pelo codigo da outra aplicação
- usando o fork e execl, o fork duplica o processo e o execl substitui um deles, não se perdendo nem " estragando" nenhuma das aplicações

- se fork = 0 -> processo filho 
- se fork != 0 -> processo pai 
- se forck == -1 -> erro 


*/

int main( int argc, char * argv[], char *envp ){

    char cmd[40];
    int continue = 1 , pid, result, state;


    while(continue){

        printf("Introduza o comando\n");
        fflush(stdout);
        scanf("%s", cmd);

        if(strcmp(cmd,"sair") != 0){

            result = fork();
            if(result == 0 ){
                pid = getpid();
                printf("[%d] Sou o filho... \n ",);
            }



        }





    }



    if(strcmp(cmd,"port")==0)
        execl(cmd,cmd,NULL);           // variante execl precisa da lista dos comandos

    if(strcmp(cmd,"ingl")==0)
        execl(cmd,cmd,NULL);   

    printf("Não consegui executar a aplicacao.\n");  //só aparece se der erro pois se tudo correr bem a aplicação é bustituida antes que chegar a este ponto     


}
