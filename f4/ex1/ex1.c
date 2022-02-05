#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int i=0;

void mostra(int s){
    printf("\n[recebi o sinal %d]    Ai!!\n" , getpid());
    i++;
    if (i==5){
        kill(getpid(),SIGKILL);  //pode não ser a melhor resolução 
    }
}

int main(int argc, char const *argv[]){
    char str[40];

    signal(SIGINT,mostra);
    printf("[ MEU PID: %d]\n",getpid() );

    do{
        printf("Nome: ");
        fflush(stdout);
        scanf("%s",str);
        printf("Ola %s!!!\n",str);

    }while(strcmp(str,"sair")!=0);

    exit(0);
}