

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

#define PPA "pipe_a"

typedef struct Message
{
    int pid;
    char str[100];

} msg;

// sigquit() function definition
void sigquit()
{
    printf("Eco vai terminar! \n");
    exit(EXIT_SUCCESS);
}

void exitByCrtlC(int s)
{
    printf("\n -> Crtl ^C Ativated ");
    exit(EXIT_SUCCESS);
}

int main(void)
{

    int fd, n;
    char str[256];
    msg sms;

    signal(SIGINT, exitByCrtlC);
    signal(SIGQUIT, sigquit);

    do
    {
        fd = open(PPA, O_WRONLY); //abre pipe com permissões de escrita

        printf("Escreva algo para o pipe: ");
        scanf("%s", sms.str);
        sms.pid = getpid();

        n = write(fd, &sms, sizeof(sms) );
        printf("Escreveu %i bytes em %s: %s\n", n, PPA, sms.str);

        close(fd);

    } while (strcmp(str, "sair"));

    return 0;
}