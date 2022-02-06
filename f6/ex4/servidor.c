// Sistemas Operativos 2021/2022

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

#define SERVER "ServerPipe"
#define CLIENT "ClientPipe%d"
int fdServer;

pthread_mutex_t mutexListaClientes;
pthread_t threadID ;



typedef struct
{
    pthread_t tid; //id da thread
    int continua;
} TDados;

typedef struct
{
    pthread_t idThread;
    int pid;
    char pipe[30];
    char nome[30];
    int saldo;
} Cliente;

#define STRSIZE 100
#define MAXCLIENTES 20
Cliente listaClientes[MAXCLIENTES];

void sayThisAndExit(char *p)
{
    perror(p);
    exit(EXIT_FAILURE);
}

void ExitByCrtlC(int s)
{

    printf("\n -> Crtl ^C Ativated ");
    
    // terminar mutex
    pthread_mutex_destroy(&mutexListaClientes);

    // "terminar" threads
    pthread_join(threadID, NULL);

    for (int i = 0; i < MAXCLIENTES; i++)
        pthread_join(listaClientes[i].idThread, NULL);

    //fechar pipe
    close(fdServer);

    // envia sinal para terminar clientes com kill(pid, SIGQUIT)
    for (int i = 0; i < MAXCLIENTES; i++)
        kill(listaClientes[i].pid, SIGQUIT);




    exit(EXIT_SUCCESS);
}

#define TOCLIENT "TOClientPipe%d"
#define FROMCLIENT "FROMClientPipe%d"

void *threadClient(void *arg)
{
    Cliente *cliente = (Cliente *)arg;
    int res, i, fdFROM, fdTO, n, continua;
    char cmd[50], cmd1[50], topipe[50], frompipe[50];
    char writeStr[100];


    sprintf(topipe, TOCLIENT, cliente->pid);
    sprintf(frompipe, FROMCLIENT, cliente->pid);
    fdTO = open( topipe, O_WRONLY | O_NONBLOCK);
    fdFROM = open(frompipe, O_RDONLY | O_NONBLOCK );
    if ( fdTO== -1 || fdFROM == -1)
        sayThisAndExit("Error pipe Client ");



    while( continua == 0 ){


    res = read( fdFROM, cmd, sizeof(cmd - 1));
    printf("\n[Cliente %s] %s", cliente->nome, cmd);

    if (strcmp(cmd, "saldo") == 0)
    {
        sprintf(writeStr, "[ %d] %s - SALDO: %d", cliente->pid, cliente->nome, cliente->saldo);
    }
    else if (strcmp(cmd, "sair") == 0)
    {
        // eliminar da lista
        for (i = 0; i < MAXCLIENTES; i++)
        {
            if (listaClientes[i].pid == cliente->pid)
            {
                listaClientes[i] = listaClientes[i + 1];
            }
        }
        sprintf(writeStr, "\nAdeus %s! ", cliente->nome);
        continua = 1; 
    }
    else
    {

        sscanf(cmd, "%s %d", cmd1, &n);

        if (strcmp(cmd, "depositar") == 0)
        {
            cliente->saldo = +n;
            sprintf(writeStr, "[ %d] %s - NOVO SALDO: %d", cliente->pid, cliente->nome, cliente->saldo);
        }
        else if (strcmp(cmd, "levantar") == 0)
        {
            cliente->saldo = -n;
            sprintf(writeStr, "[ %d] %s - NOVO SALDO: %d", cliente->pid, cliente->nome, cliente->saldo);
        }
    }
    

    // escreve

    res = write(fdTO, writeStr, sizeof(writeStr - 1));
    if (res == -1)
        sayThisAndExit("Error pipe Client ");
    }

    close(fdTO);
    close(fdFROM);
    pthread_exit(NULL);

}

void *reciveClients(void *arg)
{


    TDados *dados = (TDados *)arg;
    Cliente cliente;
    int res, i;
    char str[100];

    while (dados->continua == 1)
    {     
        

        res = read(fdServer, str, sizeof(str - 1));
        if (res == -1)
            sayThisAndExit("Error reading form server");

        
        sscanf(str, "%s %d", cliente.nome, &cliente.pid);
        printf("[CLIENTE NOVO] %s" ,cliente.nome);

        cliente.saldo = 0;

        // lancar thread do cliente
        res = pthread_create(&cliente.idThread, NULL, threadClient, (void *)&cliente);
        if (res == -1)
            sayThisAndExit("Error creating thread client");

        // mutex lock
        pthread_mutex_lock(&mutexListaClientes);

        // adicionar ao array
        for (i = 0; i < MAXCLIENTES; i++)
        {
            if (listaClientes[i].pid == 0)
                listaClientes[i] = cliente;
        }

        // mutex unlock
        pthread_mutex_unlock(&mutexListaClientes);
    }
}

int main(int argc, char *argv[])
{

    int res, i;
    char cmd[50];

    // Configurar sinais
    signal(SIGINT, ExitByCrtlC); // para interromper com Ctrl^C

    if (mkfifo(SERVER, 00777) == -1)
        sayThisAndExit("error creating pipe server");

    fdServer = open(SERVER, O_RDONLY);
    if (fdServer == -1)
        sayThisAndExit("Error opening pipe server");

    // inicializar mutex
    pthread_mutex_init(&mutexListaClientes, NULL);


    //criar thread para recolher clientes
    TDados tdados;
    tdados.continua = 1;
    res = pthread_create(&tdados.tid, NULL, reciveClients, (void *)&tdados);
    if (res == -1)
        sayThisAndExit("Error creating thread");

     threadID = tdados.tid;

    do
    {
        scanf("%s[^\n]", cmd);
        printf("Teclado: [%s]\n", cmd);

        if (strcmp(cmd, "lista") == 0)
        {
            for (int i = 0; i < MAXCLIENTES; i++)
                printf("[ %d] %s - SALDO: %d", listaClientes[i].pid, listaClientes[i].nome, listaClientes[i].saldo);
        }

    } while (strcmp(cmd, "sair") == 0);

    // terminar mutex
    pthread_mutex_destroy(&mutexListaClientes);

    // "terminar" threads
    tdados.continua = 0;
    pthread_join(tdados.tid, NULL);

    for (i = 0; i < MAXCLIENTES; i++)
        pthread_join(listaClientes[i].idThread, NULL);

    //fechar pipe
    close(fdServer);

    // envia sinal para terminar clientes com kill(pid, SIGQUIT)
    for (i = 0; i < MAXCLIENTES; i++)
        kill(listaClientes[i].pid, SIGQUIT);

    return (EXIT_SUCCESS);
}