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


#define SERVER "serverPipe"
#define CLIENT "clientePipe%d"


typedef struct Question
{
    int clientPid;
    char pipeName[100];
    char str[100];

} question;


void sayThisAndExit(char * p){
    perror(p);
    exit(EXIT_FAILURE);
}


void exitByCrtlC(int s){
    printf("\n -> Crtl ^C Ativated " );
    exit(EXIT_SUCCESS);
}

int max(int a, int b){
    return (a>b) ? a: b;
}



int main(int argc, char *argv[])
{
    int fdServer, fdClient;
    char str[100];
    question q;
    int bytes;
    float result=0;
    char pipeName[100];

    signal(SIGINT, exitByCrtlC);

    fdServer = open(SERVER, O_WRONLY);
    if (fdServer == -1)
        sayThisAndExit("Server pipe Error. Maybe Server isn't running?!?");
    

    sprintf(pipeName, CLIENT, getpid() );
    mkfifo(pipeName, 00777);

    while(1)
    {

        printf("\nIntoduza a conta a resolver: ");

        fgets(str, sizeof(str), stdin); // scanf("%s", buffer);
        if (strlen(str) > 0 && (str[strlen(str) - 1] == '\n'))
        { // se tem lá alguma coisa que termina com \n
            str[strlen(str) - 1] == '\0';
        }

        printf("[KEYBOARD: %s]\n", str);
         fflush(stdout);
        q.clientPid = getpid();
        strcpy(q.str, str);
        strcpy(q.pipeName, pipeName);


        printf("\n[TO SERVER] %s", str);
        write( fdServer, &q, sizeof(q) );
       

        fdClient = open(pipeName, O_RDONLY);
         if (fdClient == -1)
        sayThisAndExit("Client pipe error");

       read(fdClient, &result, sizeof(float) );
       printf("\n[FROM SERVER] result %f", result);

       close(fdClient);





    } 
}
