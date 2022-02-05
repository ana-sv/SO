// Sistemas Operativos 2021/2022

/*

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <signal.h>

#include <pthread.h>

#define BUFFSIZE 50
#define BUFFSIZENAME 20

#define PIPEE "esq"
#define PIPED "dir"

void sayThisAndExit(char *p)
{
    perror(p);
    exit(EXIT_FAILURE);
}

void ExitByCrtlC(int s)
{
    printf("\n -> Crtl ^C Ativated ");
    exit(EXIT_SUCCESS);
}

void sig_handler(int signal, siginfo_t *info, void *extra)
{
    if (signal == SIGINT)
    {
        printf("Recebido SIGINT! A fechar ordeiramente...\n");

        // fechar pipes

        exit(0);
    }
}


typedef struct
{
    pthread_t id;
    int cancel;
    int fdPipe;
    char pipeName[BUFFSIZENAME];
    void * retval;     // codigo de terminação da thread

} ThreadDados;

void *threadFuction(void *dados)
{
    ThreadDados *tdados = (ThreadDados *)dados;
    int n;
    char buff[BUFFSIZE];

    while (!tdados->cancel)
    {

        if ((n = read(tdados->fdPipe, buff, BUFFSIZE - 1)) == -1)
        {
            sayThisAndExit("Error reading pipe");
        }

        buff[n] = '\0';
        printf("\n%s - %s\n", tdados->pipeName, buff);
    }

    return NULL;
}


int main()
{
    char cmd[BUFFSIZE];
    int  fdEsquerdo, fdDireito, res;

    ThreadDados tdados[2];

    // signal
    struct sigaction action;
    action.sa_flags = SA_RESTART | SA_SIGINFO; // Inicializar as flags
    action.sa_sigaction = sig_handler;         //Registar função




    if (sigaction(SIGINT, &action, NULL) == -1)
        sayThisAndExit("SIGINT error");

    if( mkfifo(PIPEE, 00777) == 1 || mkfifo(PIPED, 00777) == -1 )
        sayThisAndExit("Error creating pipes");

    fdDireito = open(PIPED, O_RDWR);
    fdEsquerdo = open(PIPEE, O_RDWR);
    if( fdDireito == -1 | fdEsquerdo == -1 )
        sayThisAndExit("Error opening left pipe");


    // criar 2 threads para receber os dados de cada um dos pipes 
    strcpy(tdados[0].pipeName,"PIPE DIREITO");
    tdados[0].fdPipe = fdDireito;
    tdados[0].cancel = 0; 
    res = pthread_create( &tdados[0].id, NULL, threadFuction, &tdados[0]);
    
    strcpy(tdados[1].pipeName,"PIPE ESQUERDO");
    tdados[1].fdPipe = fdEsquerdo;
    tdados[1].cancel = 0; 
    res = pthread_create( &tdados[1].id, NULL, threadFuction, &tdados[1]);

    do{
        printf("\ncomando - ");
        scanf("%s", cmd);

    }while( strcmp(cmd,"sair"));

    
    // indicar para terminarem as threads 
    tdados[0].cancel = 1;
    tdados[1].cancel = 1;


    // esperar thread terminarem
    pthread_join(tdados[0].id, &tdados[0].retval);
    pthread_join(tdados[1].id, &tdados[1].retval);


    // fechar pipes 
    close(fdDireito);
    close(fdEsquerdo);
    unlink(PIPED);
    unlink(PIPEE);


    return(EXIT_SUCCESS);
    
}