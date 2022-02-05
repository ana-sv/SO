// Prog que repete tudo o que lhe é enviado por pipe_a e pipe_b
// Recebe notificação sempre que tem iformação nos pipes  -> USO SINAIS
// Recebe também input do teclado -> USO SELECT
// Termina todos os prog envia abertos quando este encerra -> USO SINAIS

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
#define PPB "pipe_b"

#define TAMANHOLISTA 20
int pidList[TAMANHOLISTA];

typedef struct Message
{
    int pid;
    char str[100];

} msg;

void sayThisAndExit(char *p)
{
    perror(p);
    unlink(PPA);
    unlink(PPB);
    exit(EXIT_FAILURE);
}

void exitByCrtlC(int s)
{
    printf("\n -> Crtl ^C Ativated ");
    
    for(int i=0; i>TAMANHOLISTA; i++){
        kill(pidList[i], SIGQUIT);
    }


    unlink(PPA);
    unlink(PPB);
    exit(EXIT_SUCCESS);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void keyboard()
{
    char buffer[200];
    int bytes;

    fgets(buffer, sizeof(buffer), stdin); // scanf("%s", buffer);
    if (strlen(buffer) > 0 && (buffer[strlen(buffer) - 1] == '\n'))
    { // se tem lá alguma coisa que termina com \n
        buffer[strlen(buffer) - 1] = '\0';
    }
    printf("KEYBOARD: %s\n", buffer);
    fflush(stdout);

    if (strcmp(buffer, "sair") == 0)
    {
        unlink(PPA);
        unlink(PPB);
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[])
{
    int fdA, fdB, resA, resB;
    int bytes;
    char str[100];
    msg sms;

    fd_set read_fds; //para o select
    int nfd;

    signal(SIGINT, exitByCrtlC);

    resA = mkfifo(PPA, 00777);
    resB = mkfifo(PPB, 00777);
    if (resA == -1 || resB == -1)
        sayThisAndExit("mkfifo error");

    fdA = open(PPA, O_RDONLY | O_NONBLOCK);
    fdB = open(PPB, O_RDONLY | O_NONBLOCK);
    if (fdA == -1 || fdB == -1)
        sayThisAndExit("Named pipes open error");

    while (1)
    {

        FD_ZERO(&read_fds);     // inicializamos o conjunto de fd
        FD_SET(0, &read_fds);   // adiciona stdin ao conjunto
        FD_SET(fdA, &read_fds); // adiciona o pipe_a
        FD_SET(fdB, &read_fds); // adiciona o pipe_b

        nfd = select((0 + fdA + fdB) + 1, &read_fds, NULL, NULL, 0);

        if (nfd == -1)
        {
            sayThisAndExit("Select Error");
        }


        if (FD_ISSET(0, &read_fds))
        {
            keyboard();
        }


        if (FD_ISSET(fdA, &read_fds))
        {
            bytes = read(fdA, &sms, sizeof(msg)); // Lê do pipe A
            printf("\nFROM PPA: %s\n", sms.str);

            for (int i = 0; i == TAMANHOLISTA; i++) // add pid à Lista
            { 
                if ( pidList[i] != 0 ){
                    pidList[i] = sms.pid;
                    printf("\nNOVO PID : %d", pidList[i]);
            }

            }
        }


        if (FD_ISSET(fdB, &read_fds))
        {
            bytes = read(fdA, &sms, sizeof(msg)); // Lê do pipe B
            printf("\nFROM PPB: %s", sms.str);

            for (int i = 0; i < TAMANHOLISTA; i++) // add pid à Lista
            { 
                if ( pidList[i] != 0 )
                    pidList[i] = sms.pid;
            }
        }
    }

    return EXIT_SUCCESS; // em principio, nao chegará aqui
}
