#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MYPIPE "pipeSO"
#define PIPE_P "pipeP%d"

char pipeProdutor[10]; // nome do pipe deste produtor


typedef struct Mensagem
{
    char str[100];
    char pipeName[10];

}mensagem;


void sig_handler(int signal, siginfo_t *info, void *extra){
    if(signal == SIGINT){
        printf("\nProdutor vai encerrar... ");
        unlink(MYPIPE);
        remove(pipeProdutor);
        exit(0);
    }

}


int main(void){
    int fd1,fd2, n;
    char str[256];
    mensagem sms;
    struct sigaction action;


    action.sa_flags = SA_RESTART | SA_SIGINFO; //inicializar as flags 
    action.sa_sigaction = sig_handler; //registar a função

    if(sigaction(SIGINT, &action , NULL) == -1 ){
        printf("Erro ao colocar a funcao ao servico do sinal");
        exit(0);
    }
    

    sprintf(pipeProdutor, PIPE_P, getpid() );

    mkfifo(pipeProdutor, 0777);

    strcpy(sms.pipeName, pipeProdutor);

    do{
        fd1 = open(MYPIPE, O_WRONLY); //abre pipe com permissões de escrita (bloqueante);

        printf("\nEscreva algo para o pipe: ");
        scanf("%s", sms.str);

        n = write(fd1, &sms, sizeof(sms));
        printf("\nEscreveu %i bytes em %s: -%s", n, MYPIPE, sms.str);
        if(strcmp(sms.str,"sair")== 0 ){
            break;
        }

        fd2 = open( pipeProdutor, O_RDONLY ); // abre pipe produtor para leitura (bloqueante);
        n = read( fd2, &sms, sizeof(sms));

        printf("\nECO: %s", sms.str);
        
        close(fd1);
        close(fd2);

    }while(1);

    return 0;
}