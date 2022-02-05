// Sistemas Operativos 2021/2022
// THREADS 


/*
 Neste exemplo:
 - Não inclui sincronização ( mutex,semáforos, etc)
 - É bastante simples - apenas o suficiente para mostrar criação e junção de threads
 - As tarefas das duas threads são tão parecidas que poderiam ser mais logicamente feitas pela mesma função em vez de duas funções separadas como está agora
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>



// dados de controlo para cada thread 
// definidos pelo programador conforme o que for preciso

typedef struct
{
    int continua;
    char caracter;
    int vezes;
    pthread_t tid;     //id da thread 
    void * retval;     // codigo de terminação da thread
} TDados;


// funcao de suporte ás threads
void * imprime(void * arg){
    int i;
    TDados * dados = (TDados*) arg;

    for(int i=0; i<dados->vezes; i++){
        printf("%c ", dados->caracter);
        fflush(stdout); // para o caracter aparecer logo
        sleep(1);

        if(dados->continua == 0 )
            break;
    }
    printf("\nthread %c terminou", dados->caracter );
    return NULL;
}

#define NUMTHR 3

int main(){
    int res, i;
    char temp[30];
    TDados workers[NUMTHR];

    for( i=0; i<NUMTHR ; i++){
        workers[i].continua = 1;
        workers[i].vezes = ( i+1 )*10;
        workers[i].caracter = 'A'+i;
        res = pthread_create( &workers[i].tid , NULL, imprime, (void*) &workers[i] ); 

        // &variavel para id da thread 
        // atributos default
        // funcao da thread 
        // argumento -> ptr para dados da thread (melhor workers + i )


        if( res != 0){
            perror("Erro na cricao da thread ");
            exit(1);
        }

    }
    printf( "\nmain: estou a trabahar." "\nEscreve coisas, sair para terminar\n");

    while(1){
        scanf("%s", temp);
        printf("\nDisseste: %s\n", temp);

        if( strcmp(temp,"sair") == 0){
            break;
        }
           

    }


    //indicar ás threas para terminarem
    for( i=0; i<NUMTHR; i++)
        workers[i].continua = 0 ; // nunca terminar threads à força

    //esperar que as threads terminem mesmo
    // NUNCA usar sleeps

    for(i=0; i<NUMTHR; i++)
        pthread_join(workers[i].tid, & workers[i].retval);

    printf("\ntodas as threads terminaram\n");
    printf("\nmain a encerrar\n");
    return 0; 
}



