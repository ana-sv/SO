// Sistemas Operativos 2021/2022
// VARIAVEIS CONDICIONAIS

/*

Cenário : 

- São criadas váras threads que incrementam um contador comum a todo o programa e threads, mas que NÃO É VARIAVEL GLOBAL -> DEVEM EVITAR-SE A TODO O CUSTO AS VARIAVEIS GLOBAIS 
- O valor do contador é analizado pela thread que executa a função main.
- Quando o valor atingir um determinado valor, a thread que executa a funcao main avança e faz terminar o programa



Situações de espera / Sinalização :

- A função main é a função que aguarda um acontecimento; esse acontecumento é o incremento do contador 
- A thread da função main agurada por esse acontecimento através de uma varável condicional
- Sempre que uma das restante threads incrementa esse contador, sinaliza esse acontecimento à thread da função main usando a variável condicional.


Recursos Comuns :

- o acesso ao contador constitui uma secção critica e é guardado popr um mutex
- a variavel condicional e o mutex estao assim interligados 
- a variavel condicional e o mutex são , tal como o contador, comuns a todo o programa e partilhados entre as threads

*/

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

void sayThisAndExit(char *p)
{
    perror(p);
    exit(EXIT_FAILURE);
}

void ExitByCrtlC(int s)
{
    printf("\n -> Crtl ^C Ativated ");
    exit(EXIT_SUCCESS);
}

// numero de threads a utilizar, 7 é apenas exemplo
const int NUMTHREADS = 7;

// numero de loops a utilizar , 4 é só um exemplo
const int NUMLOOPS = 4;

// estrutura de dados que as threads precisam
// inclueindo acesso à variavel partilhada "prontas", o mutex e a variavel condicional
typedef struct
{
    int *ptrProntas;
    pthread_t tid; // id da thread
    int myID;
    int myNumLoops;
    pthread_mutex_t *ptrMutex;
    pthread_cond_t *ptrCondV;
} ThreadDados;

// funcao da thread
void *funcaoThread(void *info)
{
    ThreadDados *ptrMyDados = (ThreadDados *)info; // ponteiro info aponta para a estrutura ThreadDados com o necessário de cada thread

    for (int i = 0; i < ptrMyDados->myNumLoops; i++)
    {
        printf("Thread %d working (%d de %d)\n ", ptrMyDados->myID, i, ptrMyDados->myNumLoops);
        sleep(1 + (rand() & 1)); // só para simular um trabalho qq mais demorado
    }

    // o contador está em *(ptrMyDados->ptrProntas);
    // o contador é partilhado , logo é necessário usar o mutex
    pthread_mutex_lock(ptrMyDados->ptrMutex);

    // aumenta a variavel partilhada apontada por ptr
    (*ptrMyDados->ptrProntas)++;

    printf("\nThread %d pronta. Total de threads prontas agora = %d\n", ptrMyDados->myID, *(ptrMyDados->ptrProntas));

    // assinalar a variavel condicional -> acorda a thread "main"

    pthread_cond_signal(ptrMyDados->ptrCondV);
    pthread_mutex_unlock(ptrMyDados->ptrMutex);

    return NULL;
}

int main(int argc, char *argv[])
{
    int i;

    //contador partilhado
    // é usado em paralelo(simultaneo) por isso deve ser protegido por um mutex
    // quando atinge o numero total de threads "inicial" avança
    int prontas = 0;

    // mutex e variavel condicional
    // sao dados a conhecer ás threads por ponteiro em ThreadDados
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t condv = PTHREAD_COND_INITIALIZER;

    printf("\nThread inicial a correr a função main\n");

    ThreadDados dadosthreads[NUMTHREADS];

    // cria threads
    for (i = 0; i < NUMTHREADS; i++)
    {
        dadosthreads[i].myID = i + 1;
        dadosthreads[i].ptrProntas = &prontas;
        dadosthreads[i].ptrMutex = &mutex;
        dadosthreads[i].ptrCondV = &condv;
        pthread_create(&dadosthreads[i].tid, NULL, funcaoThread, dadosthreads + i);
    }

    // fechar o mutex antes de chegar à condição do ciclo
    pthread_mutex_lock(&mutex);

    // usar um ciclo  para aguardar por todas as threads
    // no entanto este ciclo nao vai ter espera ativa devido ao uso da variavel condicional
    while (prontas < NUMTHREADS)
    {

        // aguarda sinalização da variavel condicional
        // bloqueia no wait e o mutex é libertado enquanto bloqueado
        // o mutex é automaticamente readquirido quando o wait acorda
        pthread_cond_wait(&condv, &mutex);
        printf("\nThread \"main\" acordou: prontas %d de %d ", prontas, NUMTHREADS);
    }
    
    // libertar o mutex ( porque dentro do ciclo readquiriu o mutex )
    // este unlock apos o ciclo é a ação "simetrica" do lock antes do ciclo

    pthread_mutex_unlock(&mutex);
    printf("\nThread \"main\": tudo pronto\n");

    return 0;
}
