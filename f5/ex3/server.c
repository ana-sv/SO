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
#define MAXCLIENTS 3


typedef struct Question
{
    int clientPid;
    char pipeName[100];
    char str[100];

}question;


void sayThisAndExit(char * p){
    perror(p);
    exit(EXIT_FAILURE);
}


void exitByCrtlC(int s){
    printf("\n -> Crtl ^C Ativated " );
    remove(SERVER);
    exit(EXIT_SUCCESS);
}

int max(int a, int b){
    return (a>b) ? a: b;
}

void keyboard(){
    char buffer[200];
    int bytes;

    fgets(buffer, sizeof(buffer), stdin );  // scanf("%s", buffer);
    if( strlen(buffer)>0 && (buffer[strlen(buffer)-1]=='\n')  ){ // se tem lá alguma coisa que termina com \n 
        buffer[strlen(buffer)-1] = '\0';
    } 

    printf("\nKEYBOARD -> %s", buffer);
    fflush(stdout);


    if(strcmp(buffer,"sair")==0){
          remove(SERVER);
        exit(EXIT_SUCCESS);
    }


}

float calculator(char str[100]){

    float result;
    int n1, n2;
    char op;

    sscanf(str,"%d %c %d", &n1, &op, &n2);
    
    switch (op)
    {
    case '+' :
        return n1 + n2;

    case '-' :
        return n1 - n2;

    case '*' :
        return n1 * n2;
    
    case '/' :
        return n1 / n2;
    
    default:
        return 0;
    }

}

int main(int argc, char *argv[])
{

    int fdServer, fdClient;
    int nfd;
    fd_set read_fds;
    struct timeval time;
    question q;
    int bytes;
    float result;

  printf("\nOI ");
    signal(SIGINT, exitByCrtlC);

    if (access(SERVER, F_OK) != -1)
        sayThisAndExit("Server is already running!");

    mkfifo(SERVER, 00777);
    fdServer = open(SERVER, O_RDONLY | O_NONBLOCK);
    if (fdServer == -1)
        sayThisAndExit("Open server pipe error ");


    while (1)
    {
        time.tv_sec = 0;
        time.tv_usec = 0;

        FD_ZERO(&read_fds);   // inicializamos o conjunto de fd
        FD_SET(0, &read_fds); // adiciona stdin ao conjunto
        FD_SET(fdServer, &read_fds);


        nfd = select( fdServer+1 , &read_fds, NULL, NULL, &time);
        if( nfd == -1 ){
            close(fdServer);
            unlink(SERVER);
            remove(SERVER);
            sayThisAndExit("Select Error");
        }

        if( nfd == 0 ){
            //printf("\nEstou a espera... \n ");
            fflush(stdout);
            continue;
        }

        if( FD_ISSET(0, &read_fds)){   // ler do teclado
            keyboard();
        }

        if( FD_ISSET(fdServer, &read_fds) ){
           
            bytes = read( fdServer, &q, sizeof(question) );
            printf("\n[FROM %s]  %s", q.pipeName, q.str);

            result = calculator(q.str);
            printf("\nResultado : %f", result);

            fdClient = open( q.pipeName, O_WRONLY);
            bytes = write(fdClient, &result, sizeof(float));

            close(fdClient);
        }


    }


        return EXIT_SUCCESS; // em principio, neste exemplo, nao chegará aqui

}