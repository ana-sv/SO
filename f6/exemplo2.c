// Sistemas Operativos 2021/2022
// OPERACOES DE E/S SIMULTANEAS EM VARIAS FONTES DE DADOS COM THREADS


/*
 Este exemplo trata da leitura de varias fontes em simultaneo com threads
 -> Dois names pipes e o teclado


Cenário:
Exite um processo que deve receber imput vindo de dois maned pipes e do teclado
Não se sabe qual destas fontes de dados terá dados em primeiro lugar e as operações de leitura são bloqueantes.

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


void sayThisAndExit(char * p){
    perror(p);
    exit(EXIT_FAILURE);
}


void ExitByCrtlC(int s){
    printf("\n -> Crtl ^C Ativated " );
    exit(EXIT_SUCCESS);
}




void encerra()
{
    unlink("pipe_a");
    unlink("pipe_b");
    printf("\n");
    exit(EXIT_SUCCESS);
}

//struct para o funcionamento das threads
//descritor do named pipe que vai ser lido e nome do pipe para efeitos informativos
typedef struct dados_pipes
{
    char qual[10];
    int fd;
} ThrDados;

//funcao da thread, suporta as duas threads lançadas
// a funcao mantem-se em ciclo a ler dados de um named pipe 
// o ciclo nao tem fim, a thread termina quando o processo termina 
void *trataPipes(void *p)
{

    char *qual = ((ThrDados *)p)->qual;
    int fd = ((ThrDados *)p)->fd;

    char buffer[200];
    int bytes;

    while (1)
    {
        bytes = read(fd, buffer, sizeof(buffer));
        buffer[bytes] = '\0';

        if ((bytes > 0) && (buffer[strlen(buffer) - 1] == '\n'))
            buffer[strlen(buffer) - 1] = '\0';

        printf("\n%s: (%d bytes) [%s]\n", qual, bytes, buffer);

        if (strcmp(buffer, "sair") == 0)
            encerra();
    }

    return NULL;
}

int main( int argc, char* argv[]){

    char buffer[200];
    int bytes;
    int fd_a, fd_b;     //handles para os files descriptors dos pipes 
    pthread_t tpipea, tpipeb;
    ThrDados tdados[2];     // estruturas com os dados das threads 

    signal(SIGINT, ExitByCrtlC); // para interromper com Ctrl^C 


    //cria pipes 
    mkfifo("pipe_a", 00777);
    mkfifo("pipe_b", 00777);

    // abre os pipes , leitura+escrita bloqueantes 
    fd_a = open("pipe_a", O_RDWR);
    fd_b = open("pipe_b", O_RDWR);
    if( fd_a == -1 || fd_b == -1 ){
        sayThisAndExit("Erro aos abrir pipes");
    }


    // Thread A 
    // prepara dados da thread 
    // lanca a thread
    strcpy(tdados[0].qual, "Pipe A"); 
    tdados[0].fd = fd_a;
    if( pthread_create (& tpipea, NULL, trataPipes, tdados+1) != 0 )
        sayThisAndExit("\nHouve um problema a criar a thread 1/ Pipe A ");

    // Thread B
    // prepara dados da thread 
    // lanca a thread
    strcpy(tdados[1].qual, "Pipe B"); 
    tdados[1].fd = fd_b;
    if( pthread_create (& tpipeb, NULL, trataPipes, tdados+1) != 0 )
        sayThisAndExit("\nHouve um problema a criar a thread 2/ Pipe B ");



    printf("\nReady!\n");
    while(1){
        scanf("%s[^\n]", buffer );
        printf("Teclado: [%s]\n", buffer);
        if(strcmp(buffer,"sair")==0)
            encerra();
    }



    return EXIT_SUCCESS; // em principio nao deve chegar aqui 

}