#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>


typedef struct{
    char c;
    int cancel;
}tdados;


void * imprime(void * arg){
    tdados * dados = (tdados *) arg;
    int i,n;

    while( !dados->cancel ){

        n = 1 + rand()%5 ;

        for( i=0; i<n; i++){
            printf(".");
            sleep(1);
        }

        for( i=0; i<3; i++){
            printf("%c", dados->c);
            sleep(1);
        }


    }

}


int main(int argc, char **argv) {

    char cmd[20];
    pthread_t th[2];
    tdados dadosA, dadosB;

    setbuf(stdout,NULL);
    srand(time(NULL));  

    dadosA.c = 'A';
    dadosB.c = 'B';
    dadosA.cancel = 0;
    dadosB.cancel = 0;

    // pthread_create( ponteiro p/id da thread, atributos iniciais, ponteiro p/ funcao, argumento a passar à funcao )
    pthread_create( &th[0], NULL, &imprime, &dadosA);
    pthread_create( &th[1], NULL, &imprime, &dadosB);


    printf("Insira \"sair\" para sair.\n");


    do{

        scanf("%s", cmd);

    }while(strcmp(cmd,"sair"));


    dadosA.cancel = 1; // pedir à thread para terminar
    pthread_join(th[0], NULL); // esperar que a thread acabe 


    dadosB.cancel = 1; // pedir à thread para terminar
    pthread_join(th[1], NULL); // esperar que a thread acabe 


    printf("\nadeus...");
    
    return(EXIT_SUCCESS);
}