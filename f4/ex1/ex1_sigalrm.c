#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int i=0;

void mostra(int s){
    printf("\n[recebi o sinal %d]    Ai!!\n" , getpid());
}

int main(int argc, char const *argv[]){
    char str[40];

    signal(SIGALRM,mostra);
    printf("[ MEU PID: %d]\n",getpid() );

    do{
        alarm(5);
        printf("Nome: ");
        fflush(stdout);
        scanf("%s",str);
        alarm(0); // "desliga" alarme depois de responder
        printf("Ola %s!!!\n",str);

    }while(strcmp(str,"sair")!=0);

    exit(0);
}