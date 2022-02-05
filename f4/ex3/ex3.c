#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

// exercicio incompleto 

int main(int argc, char const *argv[]){

    int pid,sinal;
    
    if(argc !=3 ){
        fprintf(stderr,"[ERRO] numero de argumentos\n" );
        exit(1);
    }

    sinal = atoi(argv[1]);
    pid = atoi(argv[2]);

    printf("Enviando sinal %d ao processo %d ....\n", sinal , pid);

    union sigval value;
    value.sival_int = 666;
    sigqueue(pid,sinal,value);

    exit(0);   

}
