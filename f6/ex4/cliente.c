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

#define TOCLIENT "TOClientPipe%d"
#define FROMCLIENT "FROMClientPipe%d"

#define SERVER "ServerPipe"
int fdServer;

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

void sigquitFunction()
{
    printf("\n -> SIGQUIT Ativated ");
    printf("\n Encerrar... ");

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

    char MyPipe[30], str[100], nome[30], cmd[30];
    int fdTO, fdFROM, res, bytes;

    // Configurar sinais
    signal(SIGINT, ExitByCrtlC); // para interromper com Ctrl^C
    signal(SIGQUIT, sigquitFunction);

    fdServer = open(SERVER, O_WRONLY);
    if (fdServer == -1)
        sayThisAndExit("Server pipe Error. Maybe Server isn't running?!?");

    printf("\nNome:");
    scanf("%s", nome);

    // escreve no pipe servidor
    sprintf(str, "%s %d", nome, getpid());
    bytes = write(fdServer, str, sizeof(str - 1));
    if (bytes == -1)
        sayThisAndExit(" Error writing to Server");


    // cria pipe from server TO CLIENT
    sprintf(MyPipe, TOCLIENT, getpid());
    res = mkfifo(MyPipe, 00777);
    fdTO = open(MyPipe, O_RDONLY | O_NONBLOCK);
    if (res == -1|| fdTO == -1 )
        sayThisAndExit("Error pipe cliente");
    
    // cria pipe to server FOM CLIENTE
    sprintf(MyPipe, FROMCLIENT, getpid());
    res = mkfifo(MyPipe, 00777);
    fdFROM = open(MyPipe, O_WRONLY | O_NONBLOCK);
    if (res == -1 || fdFROM == -1)
        sayThisAndExit("Error pipe cliente2");



    do
    {
        scanf("%s[^\n]", cmd);
        printf("[CLIENTE] %s\n", cmd);

        write(fdFROM, cmd, sizeof(cmd - 1));

        read(fdTO, str, sizeof(str-1));
       
        printf("\n[SERVIDOR] %s\n", str);

    } while (strcmp(cmd, "sair") == 0);

    close(fdTO);
    close(fdFROM);


    
}