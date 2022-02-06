// Sistemas Operativo 2021/2022

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

int fd;

void sayThisAndExit(char *p)
{
    perror(p);
    exit(EXIT_FAILURE);
}


void sig_handler(int signal, siginfo_t *info, void *extra)
{
    if (signal == SIGINT)
    {
        printf("Recebido SIGINT! A fechar...\n");
        close(fd);
        exit(0);
    }
}


void main(int argc, char **argv)
{
    int num, res;
    char str[BUFFSIZE];
    char buff[BUFFSIZE * 2];
    struct sigaction action;

    if (argc != 2)
        sayThisAndExit("Usage: ./%s <dir/esq>");
   
    action.sa_flags = SA_RESTART | SA_SIGINFO; // Inicializar as flags
    action.sa_sigaction = sig_handler;         //Registar função

    if (sigaction(SIGINT, &action, NULL) == -1)
        sayThisAndExit("Sigint error");


    fd = open(argv[1], O_WRONLY);
    if( fd == -1 )
        sayThisAndExit("Error opening pipe");


    strcpy(str, argv[1]);
    printf("Nome: %s ", str);

    while (1)
    {
        printf("Numero: ");
        scanf("%d", &num);

        sprintf(buff, "%s %d", str, num);
        res = write(fd, buff, strlen(buff));
        if ( res == -1 )
            sayThisAndExit("Error pipe writing ");
    }

    exit(0);
}