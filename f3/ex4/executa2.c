// Ana Videira - 2015012218 
// Sistemas Operativos 2021/2022

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

int main(int argc, char *argv[], char *envp)
{

    char cmd[40];
    int continua = 1, pid, result, state;

    do
    {

        printf("\n\nIntroduza o comando\n");
        fflush(stdout);
        scanf("%s", cmd);

        result = fork();

        if (result == -1)
        {
            perror("fork error" );
        }
        else if (result == 0)
        {

            pid = getpid();
            printf("[%d] Sou o filho... \n ", pid);

            execl(cmd, cmd, NULL); 
        }
        else
        {
            
            pid = getpid();
            printf("[%d] Sou o Pai... \n ", pid);


        }

    } while (strcmp(cmd, "sair") != 0);


        printf("Não consegui executar a aplicacao.\n"); //só aparece se der erro pois se tudo correr bem a aplicação é bustituida antes que chegar a este ponto

    }
